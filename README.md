# matt_daemon

Clone le projet

docker build -t matt_daemon .

docker run -it -p 4242:4242 matt_daemon




Done :
- TintinReporter : Log fichier avec timestamp
- init et ecoute sur port
- fichier lock : flock()
- tourne en tache de fond 
- Makefile
- gestion de plusieurs clients

Todo :
- forme canonique
- gestion des signaux

