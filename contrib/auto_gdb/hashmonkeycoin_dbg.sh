#!/bin/bash
# use testnet settings,  if you need mainnet,  use ~/.raptoreumcore/hashmonkeycoind.pid file instead
raptoreum_pid=$(<~/.raptoreumcore/testnet3/hashmonkeycoind.pid)
sudo gdb -batch -ex "source debug.gdb" hashmonkeycoind ${raptoreum_pid}
