import numpy as np

import cv2

# O(nm) time complexity
def get_blocks(img: np.ndarray, block_size: int=8) -> np.ndarray:
    blocks = []
    if(img.shape[0] % block_size != 0 or img.shape[1] % block_size != 0):
        pad_row = block_size - img.shape[0] % block_size
        pad_col = block_size - img.shape[1] % block_size
        img = np.pad(img, ((0, pad_row), (0, pad_col)), mode="constant")

    for i in range(0, img.shape[0], block_size):
        for j in range(0, img.shape[1], block_size):
            blocks.append(img[i:i+block_size, j:j+block_size])

    return blocks

# O((nm)^2) time complexity
def forward_transformation(block: np.ndarray, type: str="DCT") -> np.ndarray:
    if type == "DCT":
        block = block.astype(np.float64)
        dct_block = np.zeros_like(block, dtype=np.float64)
        
        m = block.shape[0] # 8 for 8x8 block
        n = block.shape[1] # 8 for 8x8 block
        
        for u in range(m):
            c_u = 1 / np.sqrt(m) if u == 0 else np.sqrt(2) / np.sqrt(m)
            
            for v in range(n):
                c_v = 1 / np.sqrt(n) if v == 0 else np.sqrt(2) / np.sqrt(n)
                sum_block = 0
                
                for x in range(m):
                    for y in range(n):
                        cos1 = np.cos((2*x + 1)*u*np.pi / (2 * m))
                        cos2 = np.cos((2*y + 1)*v*np.pi / (2 * n))
                        sum_block += block[x, y] * cos1 * cos2
                
                dct_block[u, v] = c_u * c_v * sum_block
        
        return dct_block
    
    elif type == "DFT":
        # DFT
        return []

# O(1) time complexity
def quantization(block: np.ndarray, type: str="normal", quantization_table_custom: np.ndarray=None) -> np.ndarray:
    if type == "normal":
        quantization_table = np.array([[16, 11, 10, 16, 24, 40, 51, 61],
                                        [12, 12, 14, 19, 26, 58, 60, 55],
                                        [14, 13, 16, 24, 40, 57, 69, 56],
                                        [14, 17, 22, 29, 51, 87, 80, 62],
                                        [18, 22, 37, 56, 68, 109, 103, 77],
                                        [24, 35, 55, 64, 81, 104, 113, 92],
                                        [49, 64, 78, 87, 103, 121, 120, 101],
                                        [72, 92, 95, 98, 112, 100, 103, 99]])
    elif type == "custom":
        if quantization_table_custom is None:
            raise ValueError("quantization_table_custom must be provided")
        quantization_table = quantization_table_custom
    return np.round(np.divide(block, quantization_table))