import click
from cli.config import IP
from cli import api


@click.group()
def cli():
    pass


@cli.command()
@click.option("--board", required=True, type=int, help="Serial number of board")
@click.option("--channel", required=True, type=int, help="Number of channel (0-127)")
@click.option("--voltage", required=True, type=float, help="Settable voltage")
def set_channel(board, channel, voltage):
    api.set_channel(board, channel, voltage)

@cli.command()
@click.option("--board", required=True, type=int, help="Serial number of board")
@click.option("--channel", required=True, type=int, help="Serial number of board")
def read_channel(board, channel):
    api.read_channel(board, channel)
