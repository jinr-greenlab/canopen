import requests
import sys
from cli.config import IP
from cli import convert_voltage
import yaml


test_path_to_yaml = "/home/vlad/marathon_board_canOpen/canopen/config.yaml"
def parse_yaml(path_to_yaml):
    with open(path_to_yaml, "r") as stream:
        try:
            data = yaml.safe_load(stream)
            return data
        except:
            print("ERROR: yaml file not found! Please, check the path.")
            sys.exit()

def channel_converter(channel):
    if channel<0 or channel>127:
        print("ERROR: Operating channels 0-127!")
        sys.exit()
    if 0<=channel<=31:
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

def find_volt_to_bit(board_sn, channel, voltage):
    try:
        mez = channel_converter(channel)["mez"]
        mezch = channel_converter(channel)["mezch"]
        cal_dir = parse_yaml(test_path_to_yaml)["CalibFolder"]
        file_name = cal_dir + "/board_" + str(board_sn) + "_ref2.500" + "/board_"+str(board_sn)+"_mez_"+str(mez)+"_mezch_"+str(mezch)+"_reconstruct_16384.txt"
        bit = convert_voltage.volt_to_bit(file_name, voltage)
        return bit
    except:
        sys.exit()

def find_ADC_to_volt_channel(board_sn, channel, ADC_code):
    mez = channel_converter(channel)["mez"]
    mezch = channel_converter(channel)["mezch"]
    cal_dir = parse_yaml(test_path_to_yaml)["CalibFolder"]
    file_name = cal_dir + "/board_" + str(board_sn) + "_ref2.500" + "/board_"+str(board_sn)+"_mez_"+str(mez)+"_mezch_"+str(mezch)+"_reconstruct_16384.txt"
    voltage = convert_voltage.ADC_code_to_volt(file_name, ADC_code)
    return voltage

def set_channel(board_sn, channel, voltage):
    try:
        DAC_code = find_volt_to_bit(board_sn, channel, voltage)
    except:
        print("ERROR: Calibration file not found!")
        sys.exit()
    if voltage<1 or voltage>120:
        print("ERROR: Operating voltage 1-120V!")
        sys.exit()
    data = {"board_sn": board_sn, "channel": channel, "DAC_code": str(DAC_code)}
    url ="http://" + IP + "/api/voltage/" + str(board_sn) + "/" + str(channel)
    with requests.post(url, json = data) as resp:
        message = f"status code: {resp.status_code}"
        if resp.status_code != 200:
            print(f"ERROR: {message}")
            return

def read_channel(board_sn, channel):
    url ="http://" + IP + "/api/voltage/" + str(board_sn) + "/" + str(channel)
    with requests.get(url) as resp:
        ADC_code = resp.json()["ADC_code"]
        message = f"status code: {resp.status_code}"
        if resp.status_code != 200:
            print(f"ERROR: {message}")
            return
    try:
        voltage = find_ADC_to_volt_channel(board_sn, channel, ADC_code)
    except:
        print("ERROR: Calibration file not found!")
        sys.exit()
    print(f"ADC code: {ADC_code}   Voltage: {voltage} V")
    return voltage
