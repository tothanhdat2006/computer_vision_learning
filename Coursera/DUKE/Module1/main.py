import numpy as np

import argparse
import cv2
import matplotlib.pyplot as plt

from utils.jpeg_compression import get_blocks, forward_transformation, quantization, inverse_quantization, inverse_transformation

def jpeg_compress(img: np.ndarray) -> np.ndarray:
    block_size = 8
    # Pipeline 
    blocks = get_blocks(img, block_size=block_size)
    blocks = [forward_transformation(block, type="DCT") for block in blocks]
    blocks = [quantization(block, type="normal") for block in blocks]
    
    # Reconstruction
    inversed_block = [inverse_quantization(block, type="normal") for block in blocks]
    inversed_block = [inverse_transformation(block, type="DCT") for block in blocks]

    reconstructed_image = np.zeros_like(img)
    for i in range(0, img.shape[0], block_size):
        for j in range(0, img.shape[1], block_size):
            reconstructed_image[i:i+block_size, j:j+block_size] = inversed_block.pop(0)
    return reconstructed_image # in progress


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
            
        reconstruct_image = jpeg_compress(original_image)
        mse = np.mean((original_image - reconstruct_image)**2)
        print(f"Mean Squared Error: {mse}")

        plt.figure(figsize=(12, 6))
        
        plt.subplot(1, 2, 1)
        plt.title("Original Image")
        plt.imshow(original_image, cmap='gray')

        plt.subplot(1, 2, 2)
        plt.title("Compressed Image")
        plt.imshow(reconstruct_image, cmap='gray')
        
        plt.tight_layout()
        plt.show()
        
    except Exception as e:
        print(f"Error: {e}")
        exit(1)
