## Persistência de Dados em arquivos .txt
<li>Para persistência de dados do sistema, foi utilizado um conjunto de arquivos .txt com logs de pacientes já atendidos, e a fila de atendimento em si.</li>
<li>A implementação desse sistema de persistência é básica, sendo que em toda alteração das estruturas de dados contidas no sistema, o arquivo .txt é sobrescrito.</li>
<li>Uma melhoria nesse sistema, além de armazenar em um banco de dados relacional, para maior controle, seria otimizar a forma com que as informações são gravadas.</li>

## Fluxo do programa
<p align="center">
  <img src="docs/image.png" alt="Fluxograma do programa">
</p>

<p>O fluxograma acima mostra parte do processo de atendimento de um paciente no programa. Pode-se ver que para atender o próximo paciente, o sistema primeiro verifica se a fila prioritária está vazia. Caso esteja, o paciente da Fila Padrão é atendido, caso contrário, o paciente prioritário é atendido. Com isso, o escolhido é removido da fila e adicionado à Pilha de Atendimento.</p>
<p>OBSERVAÇÃO: Esse é o fluxo padrão do núcleo do programa, é claro que para melhor gerenciamento, há opções de remoção, busca e limpeza de estruturas.</p>
