ce code est une modification de  https://github.com/nygma2004/RFID_Wiegand_MQTT code
# RFID Access Control
la wemos collecte le code et l'envoi en mqtt quand on presse ENT
le bouton de sortie se fait sur A0
Le relais de la ventouse ou de la gache sur D0
le LED du clavier (fil gris) (doit etre connecté au GND pour s'allumer vert) sur d1
le buzzer sur D3
la sortie D1 et D3 servent a activer des relais ou bien des optocoupleur (pc817) pour relier GND et LED (fil gris) ou Buzzer (fil violet)
la sortie se fait automatiquement et remonte en mqtt (sauf en cas de coupure de mqtt allez savoir pourquoi j'ai pas reussit a l'integrer)
les badges maitres ouvrent la porte si coupure de wifi ou de mqtt (mais pas en cas de connection et scénario foireux)
Le code "c'est la merde" sert a ouvrir par code en cas de coupure de wifi ou de scénario foireux 







