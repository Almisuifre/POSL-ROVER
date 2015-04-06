#!/usr/bin/python
# -*- coding: iso-8859-15 -*-

# -- IMPORTATION --

#import Tkinter as tk
import tkinter as tk

import serial

#ser = serial.Serial('/dev/ttyUSB0', 9600)

# -- VARIABLES --
serialConnection = 0
locations=['/dev/ttyUSB0', '/dev/ttyUSB1', '/dev/ttyUSB2', '/dev/ttyUSB3', '/dev/ttyS0', '/dev/ttyS1', '/dev/ttyS2', '/dev/ttyS3']

for device in locations:
    try:
        print("Tentative de connecion sur...",device)
        ser = serial.Serial(device, 9600)
        serialConnection = 1
        break
    except:
        print("Connection échoué sur",device)

# -- CLASSE FRAME GAUCHE --
class Pan1(tk.Frame):
    def __init__(self, parent):
        self.parent = parent
        tk.Frame.__init__(self, self.parent)

        self.lFControleDirection = tk.LabelFrame(self, text="Tourner sur place", padx=20, pady=20)

        self.btRG1 = tk.Button(self.lFControleDirection, text="Tourner : gauche", state=tk.NORMAL, command=tournerGaucheSurPlace)
        self.btSP = tk.Button(self.lFControleDirection, text="Roues : Sur Place", state=tk.NORMAL, command=rouesSurPlace)
        self.btRD1 = tk.Button(self.lFControleDirection, text="Tourner : droite", state=tk.NORMAL, command=tournerDroiteSurPlace)
        self.btRC1 = tk.Button(self.lFControleDirection, text="Roues : Centre", state=tk.NORMAL, command=rouesCentre)

        #Positionnement dans la grille
        self.lFControleDirection.grid(column=0, row=0)
        self.btRG1.grid(column=0, row=0)
        self.btSP.grid(column=1, row=0)
        self.btRD1.grid(column=2, row=0)
        self.btRC1.grid(column=1, row=1)


# -- CLASSE FRAME CENTRALE --
class Pan2(tk.Frame):
    def __init__(self, parent):
        self.parent = parent
        tk.Frame.__init__(self, self.parent)

        self.lFSpeed = tk.LabelFrame(self, text="Vitesse", padx=20, pady=20)
        self.lFSpeed.grid(column=0, row=0, sticky='NS')
        self.sliderSpeed = tk.Scale(self.lFSpeed, from_=100, to=50, tickinterval=2)
        self.sliderSpeed.grid(column=0, row=0)

# -- CLASSE FRAME DROITE --
class Pan3(tk.Frame):
    def __init__(self, parent):
        self.parent = parent
        tk.Frame.__init__(self, self.parent)
        self.lFControleDirect = tk.LabelFrame(self, text="Controle", padx=20, pady=20)

        #if btnsDroite == 0 :
        self.btAV = tk.Button(self.lFControleDirect, text="Avancer", state=tk.NORMAL, command=avancer)
        self.btRG2 = tk.Button(self.lFControleDirect, text="Roues : Gauche", state=tk.NORMAL, command=rouesGauche)
        self.btRC2 = tk.Button(self.lFControleDirect, text="Roue : Centre", state=tk.NORMAL, command=rouesCentre)
        self.btRD2 = tk.Button(self.lFControleDirect, text="Roues : Droite", state=tk.NORMAL, command=rouesDroite)
        self.btAR = tk.Button(self.lFControleDirect, text="Reculer", state=tk.NORMAL, command=reculer)
        self.btDG1 = tk.Button(self.lFControleDirect, text="Reculer", state=tk.NORMAL, command=rouesDiagonaleGauche)
        self.btDD1 = tk.Button(self.lFControleDirect, text="Reculer", state=tk.NORMAL, command=rouesDiagonaleDroite)
        self.btDG1 = tk.Button(self.lFControleDirect, text="Roues : Diagonale à gauche", state=tk.NORMAL, command=rouesDiagonaleGauche)
        self.btDD1 = tk.Button(self.lFControleDirect, text="Roues : Diagonale à droite", state=tk.NORMAL, command=rouesDiagonaleDroite)

        #Positionnement dans la grille
        self.lFControleDirect.grid(column=1, row=0, sticky='NS')
        self.btAV.grid(column=1, row=0)
        self.btRG2.grid(column=0, row=1)
        self.btRC2.grid(column=1, row=1)
        self.btRD2.grid(column=2, row=1)
        self.btAR.grid(column=1, row=2)
        self.btDG1.grid(column=0, row=3)
        self.btDD1.grid(column=2, row=3)

# -- CLASSE FRAME DESSOUS (LOG) --
class Pan4(tk.Frame):
    def __init__(self, parent):
        self.parent = parent
        tk.Frame.__init__(self, self.parent)

        self.log = tk.Text(self, height=10, width=100, wrap = tk.WORD)
        self.log.grid(column=0, row=0)
        self.log.insert('1.0', 'Log du programme')

# -- FONCTION TOURNER A GAUCHE SUR PLACE --
def tournerGaucheSurPlace():
    print("Tourner a gauche sur place")
    if serialConnection == 1:
        serialOrdre("!,1,0,100,1,100,0,100,1,100,*")

# -- FONCTION ROUES SUR PLACE --
def rouesSurPlace():
    print("Roues sur place")
    if serialConnection == 1:
        serialOrdre("!,2,140,40,40,140,*")

# -- FONCTION TOURNER A DROITE SUR PLACE --
def tournerDroiteSurPlace():
    print("Tourner a droite sur place")
    if serialConnection == 1:
        serialOrdre("!,1,1,100,0,100,1,100,0,100,*")

# -- FONCTION ROUES AU CENTRE --
def rouesCentre():
    print("Roues au centre")
    if serialConnection == 1:
        serialOrdre("!,2,90,90,90,90,*")

# -- FONCTION AVANCER --
def avancer():
    print("Avancer")
    if serialConnection == 1:
        serialOrdre("!,1,1,100,1,100,1,100,1,100,*")

# -- FONCTION ROUES A GAUCHE --
def rouesGauche():
    print("Roue a gauche")
    if serialConnection == 1:
        serialOrdre("!,2,70,110,70,110,*")

# -- FONCTION ROUES A DROITE --
def rouesDroite():
    print("Roue a droite")
    if serialConnection == 1:
        serialOrdre("!,2,110,70,110,70,*")

# -- FONCTION RECULER --
def reculer():
    print("Reculer")
    if serialConnection == 1:
        serialOrdre("!,1,0,100,0,100,0,100,0,100,*")

# -- FONCTION ROUES DIAGONALE A GAUCHE --
def rouesDiagonaleGauche():
    print("Roue diagonale a gauche")
    if serialConnection == 1:
        serialOrdre("!,2,70,70,70,70,*")

# -- FONCTION ROUES DIAGONALE A DROITE --
def rouesDiagonaleDroite():
    print("Roue diagonale a droite")
    if serialConnection == 1:
        serialOrdre("!,2,110,110,110,110,*")

#-- FONCTION ECRITURE SERIAL
def serialOrdre(ordre):
    data = bytearray(ordre, 'ascii')
    ser.write(data)
    print("Ordre envoyé",ordre)
        
mon_app = tk.Tk()	#Instancie la classe

pan1=Pan1(mon_app)	#Panneau Gauche
pan1.grid(column = 0, row = 0, sticky='N')

pan2=Pan2(mon_app)	#PAnneau Centrale
pan2.grid(column = 1, row = 0, sticky='N')

pan3=Pan3(mon_app)	#PAnneau Droite
pan3.grid(column = 2, row = 0, sticky='N')

pan4=Pan4(mon_app)	#PAnneau Dessous (LOG)
pan4.grid(column = 0, row = 1, columnspan = 3)

mon_app.title('POSL Rover')
mon_app.mainloop()	#Boucler
