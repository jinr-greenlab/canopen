import requests
import yaml

from cli import convert_voltage
from cli import errors
from cli.config import IP, PATH_YAML


def parse_yaml(path_to_yaml):
    try:
        with open(path_to_yaml, "r") as stream:
            data = yaml.safe_load(stream)
            return data
    except:
        return -1

def check_boards(board_sn):
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
    print(f"ADC code: {ADC_code}   Voltage: {round(voltage,4)} V")
    return {"ADC_code": ADC_code, "voltage": voltage}

def read_channels(board_sn):
    errors.error_control(check_boards(board_sn))
    node = get_node(board_sn)
    errors.error_control(node)
    channels = range(1,129)
    voltages = {}
    print("Waiting...")
    for channel in channels:
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
        voltages[channel] = {"ADC_code": ADC_code, "voltage": round(voltage,4)}
    print(f"Board_SN: {board_sn}")
    for item in voltages.keys():
        print(f"channel: {item:3}   ADC_code: {voltages[item]['ADC_code']:7}   Voltage: {voltages[item]['voltage']:7} V")
    return voltages

