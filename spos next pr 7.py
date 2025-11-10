class MemoryBlock:
    def __init__(self, size):
        self.size = size
        self.is_allocated = False

class Process:
    def __init__(self, pid, size):
        self.pid = pid
        self.size = size
        self.allocated_block_index = None



def next_fit(blocks, processes):
    start_index = 0
    for process in processes:
        allocated = False
        for i in range(start_index, len(blocks) + start_index):
            index = i % len(blocks)
            if not blocks[index].is_allocated and blocks[index].size >= process.size:
                process.allocated_block_index = index
                blocks[index].is_allocated = True
                start_index = index + 1
                allocated = True
                break
        if not allocated:
            start_index = 0

def display_allocation(processes, blocks):
    print(f"{'Process':<10}{'Size':<10}{'Block Allocated':<15}")
    for process in processes:
        if process.allocated_block_index is not None:
            print(f"{process.pid:<10}{process.size:<10}{process.allocated_block_index:<15}")
        else:
            print(f"{process.pid:<10}{process.size:<10}{'Not Allocated':<15}")

# Main Program
if __name__ == "__main__":
    blocks = [MemoryBlock(100), MemoryBlock(500), MemoryBlock(200), MemoryBlock(300), MemoryBlock(600)]
    processes = [Process(1, 212), Process(2, 417), Process(3, 112), Process(4, 426)]

  
    # Reset allocations
    for block in blocks:
        block.is_allocated = False
    for process in processes:
        process.allocated_block_index = None

    print("\nNext Fit Allocation:")
    next_fit(blocks, processes)
    display_allocation(processes, blocks)
