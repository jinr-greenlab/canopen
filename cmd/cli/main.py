import click
import requests

from cli.config import *


@click.group()
def cli():
    pass


@cli.command()
@click.option("--channel", required=True, type=int, help="Number of channel (0-127)")
@click.option("--voltage", required=True, type=str, help="Settable voltage")
def set_channel(channel, voltage):
    data = {"channel": channel, "voltage": voltage}
    url ="http://" + IP + "/api/voltage/" + str(channel)
    with requests.post(url, json = data) as resp:
        message = f"status code: {resp.status_code}"
        if resp.status_code != 200:
            print(f"Error: {message}")
            return

@cli.command()
@click.option("--channel", required=True, type=str, help="Serial number of board")
def read_channel(channel):
    url ="http://" + IP + "/api/voltage/" + channel
    with requests.get(url) as resp:
        print(resp.json())
        message = f"status code: {resp.status_code}"
        if resp.status_code != 200:
            print(f"Error: {message}")
            return
