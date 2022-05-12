from flask import Flask, jsonify
from flask_restful import Resource, Api, reqparse, abort

APP = Flask(__name__)
API = Api(APP)

parser = reqparse.RequestParser()
parser.add_argument("board", type=int)
parser.add_argument("channel", type=int)
parser.add_argument("voltage", type=float)


class SetVoltage(Resource):
    def post(self):
        args = parser.parse_args()
        board = args["board"]
        channel = args["channel"]
        voltage = args["voltage"]
        print(f"Set voltage for --> board SN: {board}, channel: {channel}, voltage: {voltage}")
API.add_resource(SetVoltage, '/api/set_channel')

class ReadVolatge(Resource):
    def post(self):
        args = parser.parse_args()
        board = args["board"]
        channel = args["channel"]
        print(f"Read voltage for --> board SN: {board}, channel: {channel}")
API.add_resource(ReadVolatge, '/api/read_channel')
