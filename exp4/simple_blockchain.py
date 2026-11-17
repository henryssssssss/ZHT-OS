import hashlib
import time
import json


class Block:
    def __init__(self, index, previous_hash, data):
        self.index = index
        self.timestamp = time.time()
        self.data = data
        self.previous_hash = previous_hash
        self.hash = self.calculate_hash()

    def calculate_hash(self):
        block_string = json.dumps(self.__dict__, sort_keys=True).encode()
        return hashlib.sha256(block_string).hexdigest()

    def recalculate_hash(self):
        content = {
            "index": self.index,
            "timestamp": self.timestamp,
            "data": self.data,
            "previous_hash": self.previous_hash,
        }
        return hashlib.sha256(json.dumps(content, sort_keys=True).encode()).hexdigest()


class Blockchain:
    def __init__(self):
        self.chain = []
        self.create_block("Genesis Block")  # 创世区块

    def create_block(self, data):
        previous_block = self.chain[-1] if self.chain else None
        previous_hash = previous_block.hash if previous_block else "0"
        block = Block(len(self.chain), previous_hash, data)
        self.chain.append(block)
        self.save_block_to_file(block)
        return block

    def save_block_to_file(self, block):
        with open('blockchain.txt', 'a') as f:
            f.write(f"{block.index},{block.timestamp},{block.data},{block.hash},{block.previous_hash}\n")

    def print_chain(self):
        for block in self.chain:
            print(f"Index: {block.index}, Timestamp: {block.timestamp}, Data: {block.data}, Hash: {block.hash}, Previous Hash: {block.previous_hash}")

    def verify_chain(self):
        for i, block in enumerate(self.chain):
            if block.hash != block.recalculate_hash():
                print(f"区块 {i} 的哈希校验失败，数据可能被篡改")
                return False
            if i > 0 and block.previous_hash != self.chain[i - 1].hash:
                print(f"区块 {i} 的前驱哈希不匹配，链已断裂")
                return False
        print(f"区块链完整性校验通过：共 {len(self.chain)} 个区块")
        return True


blockchain = Blockchain()
blockchain.create_block("First block data")
blockchain.create_block("Second block data")
blockchain.print_chain()
blockchain.verify_chain()

print("== 篡改区块 1 的数据后再次校验 ==")
blockchain.chain[1].data = "Tampered data"
blockchain.verify_chain()
