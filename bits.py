# Define the size of the grid and the number of possible orientations

grid_size = 4

num_orientations = 4


# Define all possible tetris blocks

tetris_blocks = [
    # I piece
    [
        [1, 0, 0, 0],
        [1, 0, 0, 0],
        [1, 0, 0, 0],
        [1, 0, 0, 0],
    ],
    # J piece
    [
        [0, 0, 0, 0],
        [0, 1, 1, 1],
        [0, 1, 0, 0],
        [0, 0, 0, 0],
    ],
    # L piece
    [
        [0, 0, 0, 0],
        [0, 1, 1, 1],
        [0, 0, 0, 1],
        [0, 0, 0, 0],
    ],
    # O piece
    [
        [0, 0, 0, 0],
        [0, 0, 1, 1],
        [0, 0, 1, 1],
        [0, 0, 0, 0],
    ],
    # S piece
    [
        [0, 0, 1, 0],
        [0, 0, 1, 1],
        [0, 0, 0, 1],
        [0, 0, 0, 0],
    ],
    # T piece
    [
        [0, 0, 0, 0],
        [0, 1, 1, 1],
        [0, 0, 1, 0],
        [0, 0, 0, 0],
    ],
    # Z piece
    [
        [0, 0, 0, 1],
        [0, 0, 1, 1],
        [0, 0, 1, 0],
        [0, 0, 0, 0],
    ],
]


# Function to rotate a tetris block


def rotate_block(block, direction):
    """
    Rotates a tetris block in a given direction.

    Args:
      block: A list of lists representing the tetris block.
      direction: An integer indicating the rotation direction:
        1 - Rotate 90 degrees clockwise.
        2 - Rotate 180 degrees.
        3 - Rotate 90 degrees counter-clockwise.
    Returns:
      A new list of lists representing the rotated tetris block.
    """

    if direction == 1:
        # First direction is the start
        rotated_block = block
    elif direction == 2:
        # Rotate clockwise by 90 degrees.
        rotated_block = list(zip(*reversed(block)))[::-1]
    elif direction == 3:
        # Rotate 180 degrees.
        rotated_block = [list(reversed(row)) for row in reversed(block)]
    elif direction == 4:
        # Rotate counter-clockwise by 90 degrees.
        rotated_block = list(zip(*block))[::-1]

    return rotated_block


# Generate all possible orientations for each tetris block

for block in tetris_blocks:
    print(block)
    print("\n")
    for direction in range(1, num_orientations + 1):
        # Rotate the block and convert it to a binary string
        rotated_block = rotate_block(block, direction)
        binary_string = "".join(["1" if x else "0" for row in rotated_block for x in row])

        # Add leading zeros to make the string 16 digits long
        binary_string = binary_string.zfill(grid_size * grid_size)

        # Print the binary string
        print(f"0b{binary_string}")
    print("\n")
