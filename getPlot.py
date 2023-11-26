import subprocess
import time
import shlex
import matplotlib.pyplot as plt

# Kompilacja programu
subprocess.run("g++-13 testGenerator.cpp -o testGenerator", shell=True, check=True)
subprocess.run("g++-13 dijkstra.cpp -o dijkstraNormal", shell=True, check=True)
subprocess.run("g++-13 -fopenmp dijkstraOMP.cpp -o dijkstraOMP", shell=True, check=True)
subprocess.run("g++-13 -pthread dijkstraThread.cpp -o dijkstraThread", shell=True, check=True)

# Prośba o podanie wartości początku i końca zakresu, z którego losowana będzie wielkość grafu
sRange = int(input("Podaj początek zakresu dla losowania wielkości grafu: "))
eRange = int(input("Podaj koniec zakresu dla losowania wielkości grafu: "))

threads = [1, 2, 4, 8, 16, 32, 64]  
timeNormal = []
timeOMP = []
timeThread = []

# Wykonaj komendy
subprocess.run(["./testGenerator", str(sRange), str(eRange)], stdout=open("input.txt", "w"), check=True)

subprocess.run(["./dijkstraNormal"], stdin=open("input.txt", "r"), stdout=open("output.txt", "w"), shell=True, check=True)

with open("output.txt", "r") as output_file:
    result1 = float(output_file.read().strip())

for i in range(len(threads)):
    timeNormal.append(result1)

    subprocess.run(shlex.quote("./dijkstraOMP") + " " + str(threads[i]), stdin=open("input.txt", "r"), stdout=open("outOMP.txt", "w"), check=True, shell=True)
    with open("outOMP.txt", "r") as output_file:
        result = float(output_file.read().strip())
    timeOMP.append(result)

    subprocess.run(shlex.quote("./dijkstraThread") + " " + str(threads[i]), stdin=open("input.txt", "r"), stdout=open("outThread.txt", "w"), check=True, shell=True)
    with open("outThread.txt", "r") as output_file:
        result = float(output_file.read().strip())
    timeThread.append(result)

print("timeNormal:", timeNormal)
print("timeOMP:", timeOMP)
print("timeThread:", timeThread)

# Tworzenie wykresu
plt.plot(threads, timeNormal, marker='o', label='Dijkstra')
plt.plot(threads, timeOMP, marker='o', label='Dijkstra OMP')
plt.plot(threads, timeThread, marker='o', label='Dijkstra Threads')

# Dodawanie tytułów i etykiet
plt.title('Czasy wykonania dla różnej liczby wątków')
plt.xlabel('Liczba wątków')
plt.ylabel('Czas wykonania (s)')

# Dodawanie legendy
plt.legend()

# Wyświetlanie wykresu
plt.show()