#!/usr/bin/env python3
import hashlib
import struct
import binascii

# Test our genesis block parameters
nTime = 1761208594
nNonce = 7398
nBits = 0x1e0ffff0
nVersion = 1

def sha256d(b):
    return hashlib.sha256(hashlib.sha256(b).digest()).digest()

def bits_to_target(bits):
    exp = bits >> 24
    mant = bits & 0x007fffff
    target_hex = '%064x' % (mant * (1 << (8*(exp-3))))
    return int(target_hex, 16)

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

# Test mainnet genesis
pszTimestamp = "The Times 22/Jan/2024 HashmonkeyCoin is the future of decentralized cryptocurrency"
pubkey_hex = "040184710fa689ad5023690c80f3a49c8f13f8d45b8c857fbcbc8bc4a8e4d3eb4b10f4d4604fa08dce601aaf0f470216fe1b51850b4acf21b179c45070ac7b03a9"

merkle = create_coinbase(pszTimestamp, pubkey_hex)
print("Merkle root:", merkle.hex())

header = struct.pack("<I", nVersion) + b'\x00'*32 + merkle + struct.pack("<I", nTime) + struct.pack("<I", nBits) + struct.pack("<I", nNonce)
hash_ = sha256d(header)[::-1]
print("Block hash:", hash_.hex())
print("Expected:   00000b1c5f4d9200cf1b4d1603e674638acfa20b25f4249b2c8982ce3f41f37c")

TARGET = bits_to_target(nBits)
print("Target:", hex(TARGET))
print("Hash value:", int.from_bytes(hash_, 'big'))
print("Valid:", int.from_bytes(hash_, 'big') < TARGET)
