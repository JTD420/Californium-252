#!/usr/bin/env python3
# Copyright (c) 2020 The Californium Core developers
# Distributed under the MIT software license, see the accompanying
# file COPYING or http://www.opensource.org/licenses/mit-license.php.

import argparse
import subprocess
import requests
import sys

parser = argparse.ArgumentParser(description='Script to get coins from a faucet.', epilog='You may need to start with double-dash (--) when providing californium-cli arguments.')
parser.add_argument('-c', '--cmd', dest='cmd', default='californium-cli', help='californium-cli command to use')
parser.add_argument('-f', '--faucet', dest='faucet', default='https://signetfaucet.com/claim', help='URL of the faucet')
parser.add_argument('-a', '--addr', dest='addr', default='', help='Californium address to which the faucet should send')
parser.add_argument('-p', '--password', dest='password', default='', help='Faucet password, if any')
parser.add_argument('californium_cli_args', nargs='*', help='Arguments to pass on to californium-cli (default: -signet)')

args = parser.parse_args()

if args.addr == '':
    if args.californium_cli_args == []:
        args.californium_cli_args = ['-signet']
    # get address for receiving coins
    try:
        args.addr = subprocess.check_output([args.cmd] + args.californium_cli_args + ['getnewaddress', 'faucet', 'bech32']).strip()
    except FileNotFoundError:
        print('The binary', args.cmd, 'could not be found.')
        exit()

data = {'address': args.addr, 'password': args.password}
try:
    res = requests.post(args.faucet, data=data)
except:
    print('Unexpected error when contacting faucet:', sys.exc_info()[0])
    exit()
print(res.text)
