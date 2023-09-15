function main () {
    const matrix = [[1, 2, 3], [4, 5, 6], [7, 8, 9]];

    // useful values
    const height = matrix.length;
    const width = matrix[0].length;
    
    // matrix
    for (let row of matrix) {
        console.log(row);
    }
    console.log("\n");

    matrix[1][1] = algo(height, width, matrix);
    // matrix
    for (let row of matrix) {
        console.log(row);
    }

    return 0;
}

function algo (height, width, matrix) {
    let sum = 0;

    for (let i = 0; i < height; i++) {
        for (let j = 0; j < width; j++) {
        
            if (i === 1 && j === 1) {
                for (let di = -1; di < 2; di++) {
                    for (let dj = -1; dj < 2; dj++) {
                        let ni = i + di;
                        let nj = j + dj;
                        if (matrix[ni][nj] != 5){
                            sum += matrix[ni][nj];
                        }
                    }
                }
                return sum
            }
        }
    }
}

main();