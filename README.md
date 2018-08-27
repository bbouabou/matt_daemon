# matt_daemon

Clone le projet

docker build -t matt_daemon .

docker run -it -p 4242:4242 matt_daemon

Lance le bin ./a.out




Done :
- TintinReporter : Log fichier avec timestamp
- init et ecoute sur port
- fichier lock : flock()

Todo :
- Makefile & forme canonique
- gestion de plusieurs clients
- gestion des signaux
- tourne en tache de fond ?
