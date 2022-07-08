import requests
import yaml

from cli import convert_voltage
from cli import errors
from cli.config import IP, PATH_YAML


ATTEMPTS = 5 #Attemts counter for read channel if request error
NODE_ID_MAX = 128

def convert_node_to_board_sn(node):
    if node<NODE_ID_MAX:
        data = parse_yaml(PATH_YAML)
        errors.error_control(data)
        for fnode in data["Nodes"]:
            if node == fnode["NodeID"]:
                return fnode["BoardSN"]
        return -6
    return node

def parse_yaml(path_to_yaml):
    try:
        with open(path_to_yaml, "r") as stream:
            data = yaml.safe_load(stream)
            return data
    except:
        return -1

def check_boards(board_sn):
    board_sn = convert_node_to_board_sn(board_sn)
    data = parse_yaml(PATH_YAML)
    errors.error_control(data)
    available_boards = []
    for item in data["Nodes"]:
        available_boards.append(item["BoardSN"])
    if board_sn in available_boards:
        return 0
    else:
        return -6

# FIX TITLE OF CALIB FILES (channels: 1-128)
def channel_converter(channel):
    if channel<1 or channel>128:
        return -2
    elif 1<=channel<=32:
        mez = 0
        mezch = channel - 1  # !!!!!
    elif 33<=channel<=64:
        mez = 1
        mezch = channel - 32 -1  # !!!!!
    elif 65<=channel<=96:
        mez = 2
        mezch = channel - 64 -1  # !!!!!
    elif 97<=channel<=128:
        mez = 3
        mezch = channel - 96 -1  # !!!!!
    return {"mez": mez, "mezch": mezch}

def check_voltage(voltage):
    if voltage < 1 or voltage > 120:
        return -5

def get_node(board_sn):
    data = parse_yaml(PATH_YAML)
    errors.error_control(data)
    for node in data["Nodes"]:
        if board_sn == node["BoardSN"]:
            return node["NodeID"]
    return -6

def find_volt_to_bit(board_sn, channel, voltage):
    try:
        mez = channel_converter(channel)["mez"]
        mezch = channel_converter(channel)["mezch"]
        errors.error_control(mezch)
        cal_dir = parse_yaml(PATH_YAML)["CalibFolder"]
        errors.error_control(cal_dir)
        file_name = cal_dir + "/board_" + str(board_sn) + "_ref2.500" + "/board_"+str(board_sn)+"_mez_"+str(mez)+"_mezch_"+str(mezch)+"_reconstruct_16384.txt"
        bit = convert_voltage.volt_to_bit(file_name, voltage)
        errors.error_control(bit)
        return bit
    except:
        return -3

def find_ADC_to_volt_channel(board_sn, channel, ADC_code):
    try:
        if ADC_code<15000:
            return 0.3
        mez = channel_converter(channel)["mez"]
        mezch = channel_converter(channel)["mezch"]
        errors.error_control(mezch)
        cal_dir = parse_yaml(PATH_YAML)["CalibFolder"]
        errors.error_control(cal_dir)
        file_name = cal_dir + "/board_" + str(board_sn) + "_ref2.500" + "/board_"+str(board_sn)+"_mez_"+str(mez)+"_mezch_"+str(mezch)+"_reconstruct_16384.txt"
        voltage = convert_voltage.ADC_code_to_volt(file_name, ADC_code)
        errors.error_control(voltage)
        return voltage
    except:
        return -4

def set_channel(board_sn, channel, voltage):
    board_sn = convert_node_to_board_sn(board_sn)
    errors.error_control(check_boards(board_sn))
    errors.error_control(channel_converter(channel))
    errors.error_control(check_voltage(voltage))
    DAC_code = find_volt_to_bit(board_sn, channel, voltage)
    errors.error_control(DAC_code)
    node = get_node(board_sn)
    errors.error_control(node)
    data = {"node": node, "channel": channel, "DAC_code": str(DAC_code)}
    url ="http://" + IP + "/api/voltage/" + str(node) + "/" + str(channel)
    with requests.post(url, json = data) as resp:
        message = f"status code: {resp.status_code}"
        if resp.status_code != 200:
            print(f"ERROR: {message}")
            return 0

def set_channels(board_sn, voltage):
    board_sn = convert_node_to_board_sn(board_sn)
    errors.error_control(check_boards(board_sn))
    errors.error_control(check_voltage(voltage))
    node = get_node(board_sn)
    errors.error_control(node)
    channels = range(1,129)
    for channel in channels:
        DAC_code = find_volt_to_bit(board_sn, channel, voltage)
        if DAC_code<0:
            print(f"Problem: {channel}")
        data = {"node": node, "channel": channel, "DAC_code": str(DAC_code)}
        url ="http://" + IP + "/api/voltage/" + str(node) + "/" + str(channel)
        with requests.post(url, json = data) as resp:
            message = f"status code: {resp.status_code}"
            if resp.status_code != 200:
                print(f"ERROR: {message}")
                return 0

def read_channel(board_sn, channel):
    board_sn = convert_node_to_board_sn(board_sn)
    errors.error_control(check_boards(board_sn))
    errors.error_control(channel_converter(channel))
    node = get_node(board_sn)
    errors.error_control(node)
    url ="http://" + IP + "/api/voltage/" + str(node) + "/" + str(channel)
    with requests.get(url) as resp:
        response = resp.json()
        if "error" in response:
            errors.error_control(-7)
        message = f"status code: {resp.status_code}"
        if resp.status_code != 200:
            print(f"ERROR: {message}")
            return 0
    ADC_code = response["ADC_code"]
    voltage = find_ADC_to_volt_channel(board_sn, channel, ADC_code)
    errors.error_control(voltage)
    return {"ADC_code": ADC_code, "voltage": round(voltage,4)}

def read_channels(board_sn):
    board_sn = convert_node_to_board_sn(board_sn)
    errors.error_control(check_boards(board_sn))
    node = get_node(board_sn)
    errors.error_control(node)
    channels = range(1,129)
    for channel in channels:
        url ="http://" + IP + "/api/voltage/" + str(node) + "/" + str(channel)
        for attempt in range(ATTEMPTS):
            with requests.get(url) as resp:
                response = resp.json()
                if "error" in response:
                    continue
                message = f"status code: {resp.status_code}"
                if resp.status_code != 200:
                    print(f"ERROR: {message}")
                    return 0
            ADC_code = response["ADC_code"]
            voltage = find_ADC_to_volt_channel(board_sn, channel, ADC_code)
            break
        print(f"channel: {channel:3}   ADC code: {ADC_code:7}   Voltage: {round(voltage,4):7}")
    return 0

def ref_voltage(board_sn):
    board_sn = convert_node_to_board_sn(board_sn)
    errors.error_control(check_boards(board_sn))
    node = get_node(board_sn)
    errors.error_control(node)
    url ="http://" + IP + "/api/ref_voltage/" + str(node)
    with requests.get(url) as resp:
        response = resp.json()
        if "error" in response:
            errors.error_control(-7)
        message = f"status code: {resp.status_code}"
        if resp.status_code != 200:
            print(f"ERROR: {message}")
            return 0
    ref_voltage = response["ref_voltage"]/1000  #mV --> V
    return ref_voltage

def hv_supply_voltage(board_sn):
    board_sn = convert_node_to_board_sn(board_sn)
    errors.error_control(check_boards(board_sn))
    node = get_node(board_sn)
    errors.error_control(node)
    url ="http://" + IP + "/api/ext_voltage/" + str(node)
    with requests.get(url) as resp:
        response = resp.json()
        if "error" in response:
            errors.error_control(-7)
        message = f"status code: {resp.status_code}"
        if resp.status_code != 200:
            print(f"ERROR: {message}")
            return 0
    ext_voltage = response["ext_voltage"]/1000  #mV --> V
    return ext_voltage

def mez_temp(board_sn):
    board_sn = convert_node_to_board_sn(board_sn)
    errors.error_control(check_boards(board_sn))
    node = get_node(board_sn)
    errors.error_control(node)
    mez_nums = range(1,5)
    mez_temps = {}
    for mez_num in mez_nums:
        url ="http://" + IP + "/api/mez_temp/" + str(node) + "/" + str(mez_num)
        with requests.get(url) as resp:
            response = resp.json()
            if "error" in response:
                errors.error_control(-7)
            message = f"status code: {resp.status_code}"
            if resp.status_code != 200:
                print(f"ERROR: {message}")
                return 0
        mez_temp = response["mez_temp"]  # ADC code
        mez_temps["mez "+str(mez_num)] = mez_temp
    return mez_temps

def reset(board_sn):
    board_sn = convert_node_to_board_sn(board_sn)
    errors.error_control(check_boards(board_sn))
    node = get_node(board_sn)
    errors.error_control(node)
    url ="http://" + IP + "/api/reset/" + str(node)
    with requests.get(url) as resp:
        response = resp.json()
        if "error" in response:
            print(f"Board: {board_sn} reseted!")
            return 0

def print_ref_voltage(board_sn):
    print(f"Ref. voltage: {ref_voltage(board_sn)} V")

def print_hv_supply_voltage(board_sn):
    print(f"HV power supply voltage: {hv_supply_voltage(board_sn)} V")

def print_mez_temp(board_sn):
    mez_temps = mez_temp(board_sn)
    for mez in mez_temps.keys():
        print(f"{mez}: {mez_temps[mez]}")

def print_read_channel(board_sn, channel):
    res = read_channel(board_sn, channel)
    print(f"ADC code: {res['ADC_code']}   Voltage: {res['voltage']}")
