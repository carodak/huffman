#!/usr/bin/python
# -*-coding:utf-8-*-



import os
print("======================ARCHIVE HUFFMAN======================\n")

print("Bonjour et bienvenue dans la plateforme de compression/decompression\n==Archive faite en Python 3 et s'appuie beaucoup sur les appels systems==\n")

print("SVP faites un choix \n")

print("1-Lancer le Compresseur \n") 
print("2-Lancer le Decompresseur \n") 
print("3-Quitter le programme \n") 

src=input("Entrez votre choix ")

if src==1 :
	print("\n")
	print("===============Bienvenue dans le programme de compression Huffman===============")
	print("\n")
	print("N'oubliez pas les guiellemets quand vous serez inviter à écrire ! ")
	print("\n")
	print("Veuillez choisir parmis les fichiers de votre répéretoire , le fichier à compresser ")
	print("\n")
	path = os.getcwd()
	print("\n")
	print("Analyse de", path, "en cours.")
	print("\n")
	os.system("ls -I '*.~*' -I '*.py' -I '*.c' -I '*.h' -I '*.py~' -I '*.c~' -I '*.h~'")
	print("\n")
	source=input("Choisissez (Avec des guillemets) un fichier à compressé parmis ceux listés ")
	print("\n")
	dest=input("Choisissez (Avec des guillemets) un fichier destination")
	print("Nous allons lancer la compression !")
	string="./huff_compress"
	cmd = './huff_compress '+source+' '
	cmd+=dest
	print(cmd)
	os.system(cmd)

if src==2 :
	print("\n")
	print("==============Bienvenue dans le programme de Decompression Huffman==============")
	print("\n")
	print("N'oubliez pas les guiellemets quand vous serez inviter à écrire ! ")
	print("\n")
	print("Veuillez choisir parmis les fichiers de votre répéretoire , le fichier à Decompresser ")
	print("\n")
	path = os.getcwd()
	print("\n")
	print("Analyse de", path, "en cours.")
	print("\n")
	os.system("ls -I '*.~*' -I '*.py' -I '*.c' -I '*.h' -I '*.py~' -I '*.c~' -I '*.h~'")
	print("\n")
	source=input("Choisissez (Avec des guillemets) un fichier à decompressé parmis ceux listés ")
	print("\n")
	print("Nous allons lancer la Decompression !")
	string="./huff_uncompress"
	cmd = './huff_uncompress '+source+' '
	print(cmd)
	os.system(cmd)
else :
	print("Au revoir !")
	os._exit(1)