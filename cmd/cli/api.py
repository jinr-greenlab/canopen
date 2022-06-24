import requests
import sys
import yaml

from cli import convert_voltage
from cli import errors
from cli.config import IP


test_path_to_yaml = "/home/vlad/marathon_board_canOpen/canopen/config.yaml"
def parse_yaml(path_to_yaml):
    try:
        with open(path_to_yaml, "r") as stream:
            data = yaml.safe_load(stream)
            return data
    except:
        return -1

def check_boards(board_sn):
    data = parse_yaml(test_path_to_yaml)
    errors.error_control(data)
    available_boards = []
    for item in data["Nodes"]:
        available_boards.append(item["BoardSN"])
    if board_sn in available_boards:
        return 0
    else:
        return -6

def channel_converter(channel):
    if channel<0 or channel>127:
        return -2
    elif 0<=channel<=31:
        mez = 0
        mezch = channel
    elif 32<=channel<=63:
        mez = 1
        mezch = channel - 32
    elif 64<=channel<=95:
        mez = 2
        mezch = channel - 64
    elif 96<=channel<=127:
        mez = 3
        mezch = channel - 96
    return {"mez": mez, "mezch": mezch}

def check_voltage(voltage):
    if voltage < 1 or voltage > 120:
        return -5

def find_volt_to_bit(board_sn, channel, voltage):
    try:
        mez = channel_converter(channel)["mez"]
        mezch = channel_converter(channel)["mezch"]
        errors.error_control(mezch)
        cal_dir = parse_yaml(test_path_to_yaml)["CalibFolder"]
        errors.error_control(cal_dir)
        file_name = cal_dir + "/board_" + str(board_sn) + "_ref2.500" + "/board_"+str(board_sn)+"_mez_"+str(mez)+"_mezch_"+str(mezch)+"_reconstruct_16384.txt"
        bit = convert_voltage.volt_to_bit(file_name, voltage)
        errors.error_control(bit)
        return bit
    except:
        return -3

def find_ADC_to_volt_channel(board_sn, channel, ADC_code):
    try:
        mez = channel_converter(channel)["mez"]
        mezch = channel_converter(channel)["mezch"]
        errors.error_control(mezch)
        cal_dir = parse_yaml(test_path_to_yaml)["CalibFolder"]
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
    data = {"board_sn": board_sn, "channel": channel, "DAC_code": str(DAC_code)}
    url ="http://" + IP + "/api/voltage/" + str(board_sn) + "/" + str(channel)
    with requests.post(url, json = data) as resp:
        message = f"status code: {resp.status_code}"
        if resp.status_code != 200:
            print(f"ERROR: {message}")
            return 0

def read_channel(board_sn, channel):
    errors.error_control(check_boards(board_sn))
    errors.error_control(channel_converter(channel))
    url ="http://" + IP + "/api/voltage/" + str(board_sn) + "/" + str(channel)
    with requests.get(url) as resp:
        ADC_code = resp.json()["ADC_code"]
        message = f"status code: {resp.status_code}"
        if resp.status_code != 200:
            print(f"ERROR: {message}")
            return 0
    voltage = find_ADC_to_volt_channel(board_sn, channel, ADC_code)
    errors.error_control(voltage)
    print(f"ADC code: {ADC_code}   Voltage: {voltage} V")
    return voltage
