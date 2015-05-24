#!/usr/bin/python
# -*- coding: iso-8859-15 -*-

# -- IMPORTATION --

#import Tkinter as tk
import tkinter as tk
import serial

# -- INTERFACE GRAPHIQUE
class iface1(tk.Frame):
    def __init__(self, parent):
        #Variables
        self.parent = parent
        self.serialConnection = 0
        self.locations=['/dev/ttyUSB0', '/dev/ttyUSB1', '/dev/ttyUSB2', '/dev/ttyUSB3', '/dev/ttyS0', '/dev/ttyS1', '/dev/ttyS2', '/dev/ttyS3']
        self.ser = ''
        self.currentInterface = 0

        #Les frames
        tk.Frame.__init__(self, self.parent)
        self.interfaceDirect = tk.LabelFrame(self, text="Direction standard", padx = 20, pady = 20)
        self.interfaceSurPlace = tk.LabelFrame(self, text="Direction sur place", padx = 20, pady = 20)
        self.interfaceSaisieDirect = tk.LabelFrame(self, text="Saisie de datas", padx = 20, pady = 20)
        self.interfaceSpeed = tk.LabelFrame(self, text="Vitesse", padx = 20, pady = 20)
        self.interfaceDistance = tk.LabelFrame(self, text="Distance (cm)", padx = 20, pady = 20)
        self.interfaceInfos = tk.LabelFrame(self, text="Informations", padx = 20, pady = 20)
        self.interfaceConnexion = tk.LabelFrame(self, text="Connection", padx = 20, pady = 20)
        
        #Images
        self.myImgAV = tk.PhotoImage(file="ressources/icones/av.gif")
        self.myImgRG = tk.PhotoImage(file="ressources/icones/rg.gif")
        self.myImgRC = tk.PhotoImage(file="ressources/icones/rc.gif")
        self.myImgRD = tk.PhotoImage(file="ressources/icones/rd.gif")
        self.myImgRDG = tk.PhotoImage(file="ressources/icones/rdg.gif")
        self.myImgRDD = tk.PhotoImage(file="ressources/icones/rdd.gif")
        self.myImgAR = tk.PhotoImage(file="ressources/icones/ar.gif")
        self.myImgRT = tk.PhotoImage(file="ressources/icones/rt.gif")
        self.myImgRTG = tk.PhotoImage(file="ressources/icones/rtg.gif")
        self.myImgRTD = tk.PhotoImage(file="ressources/icones/rtd.gif")
        self.myImgTSPG = tk.PhotoImage(file="ressources/icones/tspg.gif")
        self.myImgRSP = tk.PhotoImage(file="ressources/icones/rsp.gif")
        self.myImgTSPD = tk.PhotoImage(file="ressources/icones/tspd.gif")
        self.myImgCO = tk.PhotoImage(file="ressources/icones/co.gif")
        self.myImgCMD = tk.PhotoImage(file="ressources/icones/cmd.gif")
        self.myImgSD = tk.PhotoImage(file="ressources/icones/send.gif")
        
        #Boutons
        self.btAV = tk.Button(self.interfaceDirect, image=self.myImgAV, bg = "grey", command=self.av)
        self.btRG = tk.Button(self.interfaceDirect, image=self.myImgRG, bg = "grey", command=self.rg)
        self.btRC = tk.Button(self.interfaceDirect, image=self.myImgRC, bg = "grey", command=self.rc)
        self.btRD = tk.Button(self.interfaceDirect, image=self.myImgRD, bg = "grey", command=self.rd)
        self.btRDG = tk.Button(self.interfaceDirect, image=self.myImgRDG, bg = "grey", command=self.rdg)
        self.btRDD = tk.Button(self.interfaceDirect, image=self.myImgRDD, bg = "grey", command=self.rdd)
        self.btAR = tk.Button(self.interfaceDirect, image=self.myImgAR, bg = "grey", command=self.ar)
        self.btRT = tk.Button(self.interfaceDirect, image=self.myImgRT, bg = "grey", command=self.rt)
        self.btRTG = tk.Button(self.interfaceDirect, image=self.myImgRTG, bg = "grey", command=self.rtg)
        self.btRTD = tk.Button(self.interfaceDirect, image=self.myImgRTD, bg = "grey", command=self.rtd)
        self.scaleDirAV = tk.Scale(self.interfaceDirect, from_=0, to=180, orient=tk.HORIZONTAL, resolution=5, tickinterval=2)
        self.scaleDirAV.set(90)
        self.scaleDirAR = tk.Scale(self.interfaceDirect, from_=180, to=0, orient=tk.HORIZONTAL, resolution=5, tickinterval=2)
        self.scaleDirAR.set(90)
        self.currentManDir = tk.Button(self.interfaceDirect, image=self.myImgCMD, bg = "grey", command=self.manDir)
        
        self.btTSPG = tk.Button(self.interfaceSurPlace, image=self.myImgTSPG, bg = "grey", command=self.tspg)
        self.btRSP = tk.Button(self.interfaceSurPlace, image=self.myImgRSP, bg = "grey", command=self.rsp)
        self.btTSPD = tk.Button(self.interfaceSurPlace, image=self.myImgTSPD, bg = "grey", command=self.tspd)
        
        self.scaleSpeed = tk.Scale(self.interfaceSpeed, from_=255, to=80, tickinterval=2)

        self.btCo = tk.Button(self.interfaceConnexion, image=self.myImgCO, bg = "green", command=self.serialConn)

        self.btSendDirect = tk.Button(self.interfaceSaisieDirect, image=self.myImgSD, bg = "green", command=self.send_direct)

        #Saisie de texte
        self.distance = tk.Entry(self.interfaceDistance)
        self.distance.insert(0,"5")
        self.directData = tk.Entry(self.interfaceSaisieDirect)
        self.textInfos = tk.Text(self.interfaceInfos, width=50, height=20, wrap=tk.WORD)

        #Positionnement des boutons généraux
        self.interfaceDirect.grid(column=0, row=0, sticky='NS')
        self.btAV.grid(column=2, row=0)
        self.btRG.grid(column=1, row=1)
        self.btRC.grid(column=2, row=1)
        self.btRD.grid(column=3, row=1)
        self.btRDG.grid(column=0, row=1)
        self.btRDD.grid(column=4, row=1)
        self.btAR.grid(column=2, row=2)
        self.btRTG.grid(column=0, row=3)
        self.btRT.grid(column=1, row=3)
        self.btRTD.grid(column=2, row=3)
        self.scaleDirAV.grid(column=0, row=4, columnspan=5)
        self.scaleDirAR.grid(column=0, row=5, columnspan=5)
        self.currentManDir.grid(column=5, row=5, rowspan=2, columnspan=5)

        #Positionnement de la gestion de vitesse
        self.interfaceSpeed.grid(column=1, row=0, rowspan=2, sticky='NS')
        self.scaleSpeed.grid(column=0, row=0)

        #Positionnement de la gestion de la distance
        self.interfaceDistance.grid(column=1, row=1, rowspan=2, sticky='NS')
        self.distance.grid(column=0, row=0)

        #Positionnement des boutons spéciaux
        self.interfaceSurPlace.grid(column=0, row=1, sticky='NS')
        self.btTSPG.grid(column=1, row=3)
        self.btRSP.grid(column=2, row=3)
        self.btTSPD.grid(column=3, row=3)

        #Positionnement de la saisie de datas direct
        self.interfaceSaisieDirect.grid(column=0, row=2, sticky='NS')
        self.directData.grid(column=0, row=0)
        self.btSendDirect.grid(column=1, row=0);

        #Positionement du log
        self.interfaceInfos.grid(column=0, row=3, sticky='NS')
        self.textInfos.grid(column=0, row=0)

        #Positionnement de la partie connection
        self.interfaceConnexion.grid(column=1, row=3, sticky='NS')
        self.btCo.grid(column=0, row=0)

        #self.serialConn()   #Lance la connection sur le mode serial en mode automatique
        
    #Calcul du temps donné par rapport à une distance demandé
    #delay(3000) = 1 tour de roue = 18cm parcourus
    #distance (cm) * 3000 / 18 = temps à effectué.
    def distanceRoute(self):
        distanceCommand = self.distance.get() #Mise à jour de la distance
        timeRoute = ((int(distanceCommand) * 3000)/18)
        return timeRoute
    
    #Avant
    def av(self):
        speed = self.scaleSpeed.get() #Mise à jour de la vitesse
        distance = self.distanceRoute() #Récupère le temps demandé par rapport à une distance demandé
        #Si on utilise l'interface 1 
        if self.currentInterface == 1:
            #Si on a la connection lancé
            if self.serialConnection == 1:
                self.serialOrdre("!,1,1," + str(speed) + ",1," + str(speed) + ",1," + str(speed) + ",1," + str(speed) + "," + str(distance) + ",*")

    #Roues Gauches
    def rg(self):
        #Peut importe l'interface

        #Active les boutons standards
        self.btnStandard()
        
        #Si on a la connection lancé
        if self.serialConnection == 1:
            #avg / arg / avd / ard
            self.serialOrdre("!,2,70,110,75,105,*")
            self.scaleDirAV.set(70)
            self.scaleDirAR.set(110)

    #Roues Centres
    def rc(self):
        #Active les boutons standards
        self.btnStandard()
        
        #Si on a la connection lancé
        if self.serialConnection == 1:
            self.serialOrdre("!,2,90,90,90,90,*")
            self.scaleDirAV.set(90)
            self.scaleDirAR.set(90)

    #Roues Droites
    def rd(self):
        #Peut importe l'interface

        #Active les boutons standards
        self.btnStandard()

        #Si on a la connection lancé
        if self.serialConnection == 1:
            #self.serialOrdre("!,2,110,70,110,70,*")
            self.serialOrdre("!,2,105,75,110,70,*")
            self.scaleDirAV.set(110)
            self.scaleDirAR.set(70)

    #Roues Diagonales Gauches
    def rdg(self):
        #Peut importe l'interface

        #Active les boutons standards
        self.btnStandard()

        #Si on a la connection lancé
        if self.serialConnection == 1:
            self.serialOrdre("!,2,70,70,70,70,*")
            self.scaleDirAV.set(70)
            self.scaleDirAR.set(70)

    #Roues Diagolanes Droites
    def rdd(self):
        #Peut importe l'interface

        #Active les boutons standards
        self.btnStandard()
        
        #Si on a la connection lancé
        if self.serialConnection == 1:
            self.serialOrdre("!,2,110,110,110,110,*")
            self.scaleDirAV.set(110)
            self.scaleDirAR.set(110)

    #Arrières
    def ar(self):
        speed = self.scaleSpeed.get() #Mise à jour de la vitesse
        distance = self.distanceRoute() #Récupère le temps demandé par rapport à une distance demandé
        #Si on utilise l'interface 1 
        if self.currentInterface == 1:
            #Si on a la connection lancé
            if self.serialConnection == 1:
                self.serialOrdre("!,1,0," + str(speed) + ",0," + str(speed) + ",0," + str(speed) + ",0," + str(speed) + "," + str(distance) + ",*")

    #Roues Transbordeur
    def rt(self):
        #Peut importe l'interface

        #Active les boutons standards
        self.btnStandard()

        #Si on a la connection lancé
        if self.serialConnection == 1:
            #self.serialOrdre("!,2,0,10,10,5,*")
            #!,2,0,180,180,0,*
            self.serialOrdre("!,2,0,180,180,0,*")
            self.scaleDirAV.set(110)
            self.scaleDirAR.set(110)

    #Roues transbordeur avancer à gauche
    def rtg(self):
        #Si on utilise l'interface 1 
        if self.currentInterface == 1:
            #Si on a la connection lancé
            if self.serialConnection == 1:
                speed = self.scaleSpeed.get() #Mise à jour de la vitesse
                distance = self.distanceRoute() #Récupère le temps demandé par rapport à une distance demandé
                
                self.serialOrdre("!,1,1," + str(speed) + ",0," + str(speed) + ",0," + str(speed) + ",1," + str(speed) + "," + str(distance) + ",*")
                
    #Roues transbordeur avancer à gauche
    def rtd(self):
        #Si on utilise l'interface 1 
        if self.currentInterface == 1:
            #Si on a la connection lancé
            if self.serialConnection == 1:
                speed = self.scaleSpeed.get() #Mise à jour de la vitesse
                distance = self.distanceRoute() #Récupère le temps demandé par rapport à une distance demandé
                
                self.serialOrdre("!,1,0," + str(speed) + ",1," + str(speed) + ",1," + str(speed) + ",0," + str(speed) + "," + str(distance) + ",*")
                
    #Mise à jour de la direction manuelle
    def manDir(self):
        #Si on utilise l'interface 1 
        if self.currentInterface == 1:
            #Si on a la connection lancé
            if self.serialConnection == 1:
                dirAV = self.scaleDirAV.get() #Mise à jour manuelle de la direction AV
                dirAR = self.scaleDirAR.get() #Mise à jour manuelle de la direction AR

                dirAVG = dirAV
                dirARG = dirAR
                dirAVD = dirAV
                dirARD = dirAR

                #Avant gauche
                if dirAV < 85:
                    dirAVG = dirAV
                    dirAVD = dirAV+5
                    
                if dirAV < 5:
                    dirAVG = dirAV
                    dirAVD = dirAV 

                #Avant droite
                if dirAV > 100:
                    dirAVG = dirAV+5
                    dirAVD = dirAV

                if dirAV > 175:
                    dirAVG = dirAV
                    dirAVD = dirAV

                #Arrière gauche
                if dirAR < 85:
                    dirARG = dirAR-5
                    dirARD = dirAR

                if dirAR < 5:
                    dirARG = dirAR
                    dirARD = dirAR

                #Arrière droite
                if dirAR > 100:
                    dirARG = dirAR
                    dirARD = dirAR-5

                if dirAR > 175:
                    dirARG = dirAR
                    dirARD = dirAR
                
                #gauche
                #self.serialOrdre("!,2,70,110,70,110,*")
                #self.serialOrdre("!,2,70,110,75,105,*")

                #droite
                #self.serialOrdre("!,2,110,70,110,70,*")
                #self.serialOrdre("!,2,105,75,110,70,*")
                
                
                #avg / arg / avd / ard
                self.serialOrdre("!,2," + str(dirAVG) + "," + str(dirARG) +"," + str(dirAVD) + "," + str(dirARD) + ",*")
    
    #Tourner Sur Place Gauche
    def tspg(self):
        speed = self.scaleSpeed.get() #Mise à jour de la vitesse
        #Si on utilise l'interface 2 
        if self.currentInterface == 2:
            #Si on a la connection lancé
            if self.serialConnection == 1:
                self.serialOrdre("!,1,0," + str(speed) + ",1," + str(speed) + ",0," + str(speed) + ",1," + str(speed) + ",1000,*")

    #Roues Sur Place
    def rsp(self):
        #Active les boutons séciaux
        self.btnSpeciaux()
        #Si on a la connection lancé
        if self.serialConnection == 1:
            self.serialOrdre("!,2,140,40,40,140,*")

    #Tourner Sur Place à Droite
    def tspd(self):
        speed = self.scaleSpeed.get() #Mise à jour de la vitesse
        #Si on utilise l'interface 2 
        if self.currentInterface == 2:
            #Si on a la connection lancé
            if self.serialConnection == 1:
                self.serialOrdre("!,1,1," + str(speed) + ",0," + str(speed) + ",1," + str(speed) + ",0," + str(speed) + ",1000,*")
    #Initialisation du rover
    def initRover(self):
        #Active les boutons standards
        self.btnStandard()
        #Si on a la connection lancé
        if self.serialConnection == 1:
            self.serialOrdre("!,2,90,90,90,90,*")
    
    #Ecrire sur le port série l'ordre
    def serialOrdre(self, ordre):
        data = bytearray(ordre, 'ascii')
        self.ser.write(data)

        information = "Envoyé -> " + ordre + "...\n"
        self.textInfos.insert(0.0, information)
        #print("Ordre envoyé",ordre)

    #Ecrire des datats en direct
    def send_direct(self):
        self.serialOrdre(str(self.directData.get()))
        self.directData.delete(0, tk.END)
        #self.directData.insert("")
        

    #Active les boutons standard
    def btnStandard(self):
        #Si on a la connection lancé
        if self.serialConnection == 1:
            self.btAV.configure(bg = "green")
            self.btRG.configure(bg = "green")
            self.btRC.configure(bg = "grey")
            self.btRD.configure(bg = "green")
            self.btRDG.configure(bg = "green")
            self.btRDD.configure(bg = "green")
            self.btAR.configure(bg = "green")
            self.btRTG.configure(bg = "green")
            self.btRT.configure(bg = "green")
            self.btRTD.configure(bg = "green")
            self.currentManDir.configure(bg = "green")
            self.btTSPG.configure(bg = "red")
            self.btRSP.configure(bg = "blue")
            self.btTSPD.configure(bg = "red")
            #Pour se rappeler dans quelle interface on est
            self.currentInterface = 1

    #Active les boutons spéciaux
    def btnSpeciaux(self):
        #Si on a la connection lancé
        if self.serialConnection == 1:
            self.btAV.configure(bg = "red")
            self.btRG.configure(bg = "green")
            self.btRC.configure(bg = "blue")
            self.btRD.configure(bg = "green")
            self.btRDG.configure(bg = "green")
            self.btRDD.configure(bg = "green")
            self.btAR.configure(bg = "red")
            self.btRTG.configure(bg = "red")
            self.btRT.configure(bg = "blue")
            self.btRTD.configure(bg = "red")
            self.currentManDir.configure(bg = "red")
            self.btTSPG.configure(bg = "green")
            self.btRSP.configure(bg = "grey")
            self.btTSPD.configure(bg = "green")
            #Pour se rappeler dans quelle interface on est
            self.currentInterface = 2

    #Etablir une connexion
    def serialConn(self):
        #Tentative de connexion au XBee Usb
        for device in self.locations:
            try:
                information = "Tentative de connecion sur le port" + device + "...\n"
                self.textInfos.insert(0.0, information)

                self.ser = serial.Serial(device, 9600)
                self.serialConnection = 1
                break
            except:
                information = "Connection échoué sur " + device + "!\n"
                self.textInfos.insert(0.0, information)

        #Si la connexion est assuré
        if self.serialConnection == 1:
            self.initRover()    #Lancer l'initialisation du rover

posl_app = tk.Tk()              #Instancie la classe

iface_graphique = iface1(posl_app)
iface_graphique.grid(column = 0, row = 0, sticky='NS')

posl_app.title('POSL Rover')    #Titre de l'application
posl_app.mainloop()             #Boucler
