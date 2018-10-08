		////////////COMPRESSEUR DE HUFFMAN\\\\\\\\\\\\\\\



Utilisation du programme de compression/décompression Huffman.

1) Compiler en utilisant le Makefile,
   	    Makefile fourni avec l'option -g (GDB)

2) Lancer dans un terminal :
	-(./)huffman_compress pour lancer le compresseur
	-(./)huffman_uncompress pour lancer le décompresseur

Plus d'informations : voir la doc html (générée avec Doxygen).

Si utilisation du compresseur à l'aide du script python : le script doit être dans le même dossier que les applications huffman_compress et huffman_uncompress pour la compression et décompression du fichier se fait alors à travers des appels systems.
En ce qui concerne la compression , il faut spécifier le fichier source , et le fichier destination avec des "" , vous aurez le meme noms passés en paramètres pour le fichier destination .
Il suffit ensuite de lancer le script python depuis le terminal (Avec ./huffman.py) et de suivre les instructions. Attention à bien utiliser avec Python 3+.

Pour le cas particulier :  Le fichier contient un unique char ( qui peut etre répété plusieurs fois )

On choisit de passer par une petite astuce , on écrit un - pour indiquer qu'on se trouve dans ce cas particulier , ce '-' suivi du nombre de char , et du char en question
La (dé)compression se fait assez facilement .
