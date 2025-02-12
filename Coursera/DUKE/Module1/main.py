import numpy as np

import argparse
import cv2
import matplotlib.pyplot as plt

from utils.jpeg_compression import get_blocks, forward_transformation, quantization

def jpeg_compress(img: np.ndarray) -> np.ndarray:
    # Pipeline 
    blocks = get_blocks(img)
    blocks = [forward_transformation(block, type="DCT") for block in blocks]
    blocks = [quantization(block, type="normal") for block in blocks]
    
    # Reconstruction
    return [] # in progress


def get_args():
    parser = argparse.ArgumentParser(description="Compress image in jpeg type")
    parser.add_argument("--source", help="Source image path", type=str)
    parser.add_argument("--resize", help="Resize image (--resize W H)", type=int, nargs='+')
    return parser.parse_args()


if __name__ == "__main__":
    args = get_args()

    print(f"Source image path: {args.source}")
    try: 
        original_image = cv2.imread(args.source, cv2.IMREAD_GRAYSCALE)
        if original_image is None:
            raise FileNotFoundError(f"Could not load image from {args.source}")
            
        if args.resize:
            original_image = cv2.resize(original_image, (args.resize[0], args.resize[1]))
            
        compressed_image = jpeg_compress(original_image)

        plt.figure(figsize=(12, 6))
        
        plt.subplot(1, 2, 1)
        plt.title("Original Image")
        plt.imshow(original_image, cmap='gray')

        plt.subplot(1, 2, 2)
        plt.title("Compressed Image")
        plt.imshow(compressed_image, cmap='gray')
        
        plt.tight_layout()
        plt.show()
        
    except Exception as e:
        print(f"Error: {e}")
        exit(1)
