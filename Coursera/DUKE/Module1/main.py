import numpy as np

import argparse
import cv2

from utils.jpeg_compression import get_blocks, forward_transformation, quantization

def jpeg_compress(img: np.ndarray) -> np.ndarray:
    # Pipeline 
    blocks = get_blocks(img)
    blocks = [forward_transformation(block, type="DCT") for block in blocks]
    blocks = [quantization(block, type="NASA") for block in blocks]
    
    # Reconstruct image
    rows = img.shape[0] // 8
    cols = img.shape[1] // 8
    compressed_img = np.zeros_like(img, dtype=np.float64)
    
    for i in range(rows):
        for j in range(cols):
            block_idx = i * cols + j
            compressed_img[i*8:(i+1)*8, j*8:(j+1)*8] = blocks[block_idx]
    
    compressed_img = np.clip(compressed_img, 0, 255).astype(np.uint8)
    return compressed_img

def get_args():
    parser = argparse.ArgumentParser(description="Compress image in jpeg type")
    parser.add_argument("--source", help="Source image path", type=str)
    return parser.parse_args()

if __name__ == "__main__":
    args = get_args()

    print(f"Source image path: {args.source}")
    try: 
        original_image = cv2.imread(args.source)
    except Exception as e:
        print(f"Error: {e}")
        exit(1)
    
    compressed_image = jpeg_compress(original_image)
    cv2.imshow('Original', original_image)
    cv2.imshow('Compressed', compressed_image)
    cv2.waitKey(0)
    cv2.destroyAllWindows()