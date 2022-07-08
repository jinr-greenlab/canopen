import click
from cli import api


@click.group()
def cli():
    pass


@cli.command()
@click.option("--board", required=True, type=int, help="Serial number of board")
@click.option("--channel", required=True, type=int, help="Number of channel (1-128)")
@click.option("--voltage", required=True, type=float, help="Settable voltage")
def set_channel(board, channel, voltage):
    api.set_channel(board, channel, voltage)

@cli.command()
@click.option("--board", required=True, type=int, help="Serial number of board")
@click.option("--voltage", required=True, type=float, help="Settable voltage")
def set_channels(board, voltage):
    api.set_channels(board, voltage)

@cli.command()
@click.option("--board", required=True, type=int, help="Serial number of board")
@click.option("--channel", required=True, type=int, help="Number of channel (1-128)")
def read_channel(board, channel):
    api.print_read_channel(board, channel)

@cli.command()
@click.option("--board", required=True, type=int, help="Serial number of board")
def read_channels(board):
    api.read_channels(board)

@cli.command()
@click.option("--board", required=True, type=int, help="Serial number of board")
def ref_voltage(board):
    api.print_ref_voltage(board)

@cli.command()
@click.option("--board", required=True, type=int, help="Serial number of board")
def hv_supply_voltage(board):
    api.print_hv_supply_voltage(board)

@cli.command()
@click.option("--board", required=True, type=int, help="Serial number of board")
def mez_temp(board):
    api.print_mez_temp(board)

@cli.command()
@click.option("--board", required=True, type=int, help="Serial number of board")
def reset(board):
    api.reset(board)

# @cli.command()
# @click.option("--board", required=True, type=int, help="Serial number of board")
# def test(board):
#     print(api.convert_node_to_board_sn(board))

