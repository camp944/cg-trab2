import cv2
import numpy as np

# Carregue a imagem
caminho_da_imagem = 'gamewin.png'
imagem = cv2.imread(caminho_da_imagem)
imagem = cv2.cvtColor(imagem, cv2.COLOR_BGR2RGB)


# Verifique se a leitura da imagem foi bem-sucedida
if imagem is None:
    print("Erro ao carregar a imagem. Verifique o caminho.")
else:
    print(imagem.shape)
    # Converta a matriz em um vetor único
    vetor_imagem = np.reshape(imagem, (-1, 3))

    # Crie uma única string com os valores dos pixels separados por vírgulas
    matriz_unica = ','.join(map(str, vetor_imagem.flatten()))
    
with open('textura.txt', 'w') as f:
    f.write(matriz_unica)