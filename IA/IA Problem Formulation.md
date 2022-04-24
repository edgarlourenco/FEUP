# Problem Formulation

## State Representation

* Vetor 2D (Cada espaço da grelha pode ter X para o caminho, . Espaço Vazio, A-Z/{X} para o resto do alfabeto) - Grid
* Set de letras dos blocos atravessados pelo caminho. - CrossedBlocks
* Inteiros para representar a posição do último X. - [Row, Col]

## Initial State

* Uma grelha de tamanho arbirtrário com certo de numéro de blocos e espaços vazios e o X do caminho inicial no canto inferior esquerdo.

## Objective State

* Grelha com X no canto superior direito e o set das letras tem de ser igual ao set de todas as letras presentes na grelha.

## Operators

* UP, DOWN, LEFT, RIGHT

| Name  | Precond                                                                 | Effects                          | Cost |
| ----- | ----------------------------------------------------------------------- | -------------------------------- | ---- |
| UP    | [Row+1, Col] = '.' V CrossedBlocks ∌ [Row+1, Col] V [Row+1, Col] != 'X' | Row = Row + 1 e [Row, Col] = 'X' | 1    |
| DOWN  | [Row-1, Col] = '.' V CrossedBlocks ∌ [Row-1, Col] V [Row-1, Col] != 'X' | Row = Row - 1 e [Row, Col] = 'X' | 1    |
| LEFT  | [Row, Col-1] = '.' V CrossedBlocks ∌ [Row, Col-1] V [Row, Col-1] != 'X' | Col = Col - 1 e [Row, Col] = 'X' | 1    |
| RIGHT | [Row, Col+1] = '.' V CrossedBlocks ∌ [Row, Col+1] V [Row, Col+1] != 'X' | Col = Col + 1 e [Row, Col] = 'X' | 1    |

Falta o Out of Bounds.
