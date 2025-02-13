import numpy as np

def get_blocks(img: np.ndarray, block_size: int=8) -> np.ndarray:
    '''
    Get blocks of (block_size, block_size) from image

    Args:
    - img: image to be divided into blocks
    - block_size: size of block

    Returns:
    - blocks: list of blocks
    '''
    blocks = []
    if img.shape[0] % block_size != 0 or img.shape[1] % block_size != 0:
        pad_row = block_size - img.shape[0] % block_size
        pad_col = block_size - img.shape[1] % block_size
        img = np.pad(img, ((0, pad_row), (0, pad_col)), mode="constant")

    for i in range(0, img.shape[0], block_size):
        for j in range(0, img.shape[1], block_size):
            blocks.append(img[i:i+block_size, j:j+block_size])

    return blocks

def forward_transformation(block: np.ndarray, type: str="DCT") -> np.ndarray:
    '''
    DCT or DFT transformation of block

    Args:
    - block: block to be transformed
    - type: type of transformation

    Returns:
    - transformed block: block after transformation
    '''
    transformed_block = []
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
        
        transformed_block = dct_block
    
    elif type == "DFT":
        # DFT
        transformed_block = []

    return transformed_block
    
def quantization(block: np.ndarray, type: str="normal", quantization_table_custom: np.ndarray=None) -> np.ndarray:
    '''
    Quantization of block

    Args: 
    - block: block to be quantized
    - type: type of quantization
    - quantization_table_custom: custom quantization table

    Returns:
    - quantized block: block after quantization
    '''
    quantization_table = []
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
        
    quantized_block = np.round(block / quantization_table)
    return quantized_block

def inverse_transformation(block: np.ndarray, type: str="DCT") -> np.ndarray:
    '''
    Inverse transformation of DCT or DFT

    Args:
    - block: transformed block to be inverse transformed
    - type: type of transformation

    Returns:
    - inverse transformed block: block after inverse transformation
    '''
    inverse_transformed_block = []
    if type == "DCT":
        block = block.astype(np.float64)
        inverse_dct_block = np.zeros_like(block, dtype=np.float64)
        
        m = block.shape[0] # 8 for 8x8 block
        n = block.shape[1] # 8 for 8x8 block
        
        for x in range(m):
            for y in range(n):
                sum_block = 0
                for u in range(m):
                    c_u = 1 / np.sqrt(m) if u == 0 else np.sqrt(2) / np.sqrt(m)
                    for v in range(n):
                        c_v = 1 / np.sqrt(n) if v == 0 else np.sqrt(2) / np.sqrt(n)
                        cos1 = np.cos((2*x + 1)*u*np.pi / (2 * m))
                        cos2 = np.cos((2*y + 1)*v*np.pi / (2 * n))
                        sum_block += c_u * c_v * block[u, v] * cos1 * cos2
                
                inverse_dct_block[x, y] = sum_block
        
        inverse_dct_block = np.clip(inverse_dct_block, 0, 255) # Clip values to valid range
        inverse_dct_block = inverse_dct_block.astype(np.uint8) # Convert back to uint8
        inverse_transformed_block = inverse_dct_block
    
    elif type == "DFT":
        # DFT
        inverse_transformed_block = []

    return inverse_transformed_block


def inverse_quantization(quantized_block: np.ndarray, type: str="normal", quantization_table_custom: np.ndarray=None) -> np.ndarray:
    '''
    Inverse quantization of block

    Args:
    - quantized_block: quantized block to be inverse quantized
    - type: type of quantization
    - quantization_table_custom: custom quantization table

    Returns:
    - inverse quantized block: block after inverse quantization
    '''
    quantization_table = []
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
        
    inverse_quantization_block = quantized_block * quantization_table
    return inverse_quantization_block
