/*
Question 1.2

Le message s'affiche lorsqu'on met l'option -s INT mais sans kill envoie le signal SIGTERM par défaut qui n'est donc pas traité par le sigaction.
Pour afficher le message, il suffit d'ajouter une reception sigaction(SIGTERM, &act, NULL); dans le main. Cependant sur Mac cela ne fonctionne pas.

Le signal Kill ne peut être traité, il est donc impossible d'afficher le message.
Lorssqu'on donne le processus père :
    - avec -s KILL : la bash est interrompu
    - sans : il ne se passe rien 

Question 1.3

en faisant :
    - CTRL-C : exit_message est appelée
    - kill : exit_message est appelée
    - kill -9 : n'appelle pas exit_message

Question 2-1

En enlevant le changement de la variable running : 
    -le programme ne s'arrête pas avec CTRL-C mais au bout du 2ème le handler est appelé
    - même chose pour kill
    - Kill -9 arrête le processus sans appeler le handler


Pour distinguer les deux messages on peut différencier les PIDs, celui duppliqué avec fork() vaut 0


Le processus fils s'arrête, et seul le père continue.
Dans ps a on peut voir que le processus est toujours existant mais en mode zombie (Z+)

Lorsqu'on tue le père, les deux processus disparaissent.

Question 2-2

Lorsqu'on kill le fils, le pere meurt car plus personne à écouter
alors que kill le père n'empêche pas le fils d'ecouter 

On gère donc la fin des deux processus dans le handler, on vérifie qu'on voit bien le atexit dans les deux cas

Question 3

On crée notre fifo et notre transmission de message.
La gestion de l'arrêt se fait comme ceci : 
-lorsqu'on tue le serveur, il gère son signal et ferme le fichier, et n'enverra plus de message. Le client s'arrêt lorsqu'il tente de lire une entrée vide.
-lorsqu'on tue le client, le serveur essaye de dialoguer avec une ressource avec laquelle il est déconnecté et reçoit donc un signal PIPE qu'on utilise pour arrêter le serveur


*/