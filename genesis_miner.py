#!/usr/bin/env python3
import hashlib
import struct
import time
import binascii

# HashmonkeyCoin Regtest Genesis Parameters
pszTimestamp = "HashmonkeyCoin Regtest Genesis - 2025 Launch"
pubkey_hex = "04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f"
nBits = 0x1e0ffff0
nVersion = 1
nTime = int(time.time())
start_nonce = 0

def sha256d(b):
    return hashlib.sha256(hashlib.sha256(b).digest()).digest()

def bits_to_target(bits):
    exp = bits >> 24
    mant = bits & 0x007fffff
    target_hex = '%064x' % (mant * (1 << (8*(exp-3))))
    return int(target_hex, 16)

TARGET = bits_to_target(nBits)
print("Target:", hex(TARGET))

def create_coinbase(pszTimestamp, pubkey_hex):
    version = struct.pack("<I", 1)
    vin_cnt = b'\x01'
    prev_out = b'\x00'*32
    prev_index = struct.pack("<I", 0xffffffff)
    script = bytes([len(pszTimestamp)]) + pszTimestamp.encode()
    script_len = bytes([len(script)])
    seq = struct.pack("<I", 0xffffffff)
    vout_cnt = b'\x01'
    value = struct.pack("<Q", 500 * 100000000)  # 500 HMNY
    pubkey = binascii.unhexlify(pubkey_hex)
    scriptpk = bytes([len(pubkey)+2]) + b'\x41' + pubkey + b'\xac'
    scriptpk_len = bytes([len(scriptpk)])
    locktime = struct.pack("<I", 0)
    tx = version + vin_cnt + prev_out + prev_index + script_len + script + seq + vout_cnt + value + scriptpk_len + scriptpk + locktime
    txid = sha256d(tx)[::-1]
    return txid[::-1]

merkle = create_coinbase(pszTimestamp, pubkey_hex)
print("Merkle root:", merkle.hex())

nonce = start_nonce
while True:
    header = struct.pack("<I", nVersion) + b'\x00'*32 + merkle + struct.pack("<I", nTime) + struct.pack("<I", nBits) + struct.pack("<I", nonce)
    hash_ = sha256d(header)[::-1]
    if int.from_bytes(hash_, 'big') < TARGET:
        print("FOUND!")
        print("nTime:", nTime)
        print("nNonce:", nonce)
        print("hash:", hash_.hex())
        print("merkle:", merkle.hex())
        break
    if nonce % 500000 == 0:
        print("Nonce:", nonce, "time:", nTime)
    nonce += 1
    if nonce > 0xffffffff:
        nTime += 1
        nonce = 0
