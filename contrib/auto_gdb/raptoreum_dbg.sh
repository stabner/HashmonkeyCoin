#!/bin/bash
# use testnet settings,  if you need mainnet,  use ~/.hashmonkeycoincore/hashmonkeycoind.pid file instead
hashmonkeycoin_pid=$(<~/.hashmonkeycoincore/testnet3/hashmonkeycoind.pid)
sudo gdb -batch -ex "source debug.gdb" hashmonkeycoind ${hashmonkeycoin_pid}
