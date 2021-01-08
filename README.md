# CS50x-projects
Projetos que foram feitos durante a week 3 do CS50x.

runoff.c e plurality.c consistem em programas que simulam o processo eleitoral similar ao dos EUA.

O plurality foi o primeiro e mais simples que projetei baseado nas seguintes especificações:

- A eleição pode levar no máximo 9 candidatos.
- O votante terá de votar através do nome exato do candidato.
- Votos para candidatos que não existem serão invalidados.
- O programa vai exibir o nome do candidato vencedor se só houver 1 vencedor.
- Em caso de empate o programa vai exibir o nome dos candidatos vencedores que empataram.


O programa irá de comportar de acordo com os seguintes exemplos:

$ ./plurality Alice Bob
Number of voters: 3
Vote: Alice
Vote: Bob
Vote: Alice
Alice

$ ./plurality Alice Bob
Number of voters: 3
Vote: Alice
Vote: Charlie
Invalid vote.
Vote: Alice
Alice

$ ./plurality Alice Bob Charlie
Number of voters: 5
Vote: Alice
Vote: Charlie
Vote: Bob
Vote: Bob
Vote: Alice
Alice
Bob


O runoff consiste numa versão mais complexa e similar ao processo eleitoral existente, nele o eleitor pode elaborar uma lista de preferência de candidatos. O programa irá iterar sobre a primeira opção de cada votante e eleger o candidato somente se ele possuir mais de 50% dos votos totais, caso contrário o programa irá iterar novamente sobre os eleitores porém considerando o segundo candidato do eleitor caso a primeira opção dele tenha sido minoria na última iteração.  

O programa segue as seguintes especificações:

- A eleição poderá ter no máximo 9 candidatos.
- O eleitor terá que digitar o nome exato dos candidatos.
- Votos para candidatos inexistentes serão anulados.
- O programa irá exibir o vencedor se não houver empate.
- Em caso de empate entre todos os candidatos restantes não haverá mais eliminações.



O programa irá de comportar de acordo com os seguintes exemplos:

./runoff Alice Bob Charlie
Number of voters: 5
Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Alice
Rank 2: Charlie
Rank 3: Bob

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Bob
Rank 2: Charlie
Rank 3: Alice

Rank 1: Charlie
Rank 2: Alice
Rank 3: Bob

Alice
