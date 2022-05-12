import click
import requests

from cli.api import APP
from cli.config import *


@click.group()
def cli():
    pass


@cli.command()
@click.option("--host", default="0.0.0.0", help="server host", envvar="HOST")
@click.option("--port", default=5000, type=int, help="server port", envvar="PORT")
def run_server(host, port):
    APP.run(host=host, port=port, debug=True)


@cli.command()
@click.option("--board", required=True, type=int, help="Serial number of board")
@click.option("--channel", required=True, type=int, help="Number of channel (0-127)")
@click.option("--voltage", required=True, type=float, help="Settable voltage")
def set_channel(board, channel, voltage):
    buf = {"board": board, "channel": channel, "voltage": voltage}
    with requests.post("http://" + IP + "/api/set_channel", json=buf) as resp:
        message = f"status code: {resp.status_code}"
        if resp.status_code != 200:
            print(f"Error: {message}")
            return

@cli.command()
@click.option("--board", required=True, type=int, help="Serial number of board")
@click.option("--channel", required=True, type=int, help="Number of channel (0-127)")
def read_channel(board, channel):
    buf = {"board": board, "channel": channel}
    with requests.post("http://" + IP + "/api/read_channel", json=buf) as resp:
        message = f"status code: {resp.status_code}"
        if resp.status_code != 200:
            print(f"Error: {message}")
            return
