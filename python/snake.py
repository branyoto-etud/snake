from upemtk import *
from time import *
from random import *

L = ['darkgreen',3,10,[15,40,30],'Y','green','N',2,'green']
Power_up = [['gold','yellow'],['darkgrey','grey'],['darkblue','blue'],['#BF00BF','#D900D9']]
Couleurs2 = ['green','#00E307','#FF8D00','#FFFF42','#906806','red','#FB35C5','#A000FF','#1EADFF','#0000FF','black','#A4A4A4']
Couleurs = ['darkgreen','green','#FF6A00','#FFFF06','#6B4C01','darkred','#FF03BB','#7300B6','#0E9BED','#0000AB','black','#808080']
''' La liste L contient: la couleur du serpent en solo, la difficulté,
la vittesse, une liste avec la taille des cases,la largeur et
la hauteur du plateau, si l'écran est torique, une valeur 
qui sert pour l'affichage, si le mode de difficulté est 'Hard',
et le nombre de joueurs.
La liste Power_up contient les couleurs des différentes bonus.
Les deux listes Couleurs servent pour afficher les couleurs du
serpent. (Couleur est le contour extérieur et Couleur2 le remplissage)
'''

'''
La première partie est surtout composée d'affichage
de texte dans des boutons clicables.
Donc pour expliquer c'est simple juste du texte et
des rectangles et en fonction de l'endroit où l'utilisateur
à cliqué.
'''

def menu_principal(L):
    '''
    Interface du menu.
    '''
    while True:
        ferme_fenetre()
        cree_fenetre(600,400)
        efface_tout()
        rectangle(200,160,400,200,'black','#A9A9A9')
        rectangle(200,250,400,290,'black','#A9A9A9')
        rectangle(560,360,599,399,'black','#A9A9A9')
        rectangle(1,360,100,399,'black','#A9A9A9')
        texte(270,160,'Play')
        texte(250,250,'Option')
        texte(185,20,'SNAKE','black','nw',"Purisa",50)
        texte(18,361,'Aide')
        
        rectangle(570,363,590,396,'#8D3500','#C74B00',3)
        cercle(585,380,3,'#C69803','#FFE100')
        x,y,z = attente_clic()
        if 200<=x<=400:
            if 160<=y<=200:
                choix_mode_jeu(L)
            elif 250<=y<=290:
                L = choix_option(L)
        elif 560<=x<=600:
            if 360<=y<=400:
                break
        elif 0<=x<=100:
            if 360<=y<=400:
                aide()

def aide():
    '''
    Page de données pour savoir les effets des bonus.
    '''
    efface_tout()
    texte(294,30,'Aide')
    texte(201,90,'Pomme classique')
    texte(71,150,'Pomme avariée (diminue le serpent)')
    texte(140,210,'Pomme métalique (ralenti)')
    texte(152,270,'Pomme éclair (accélère)')
    texte(83,330,'Pomme colorée (modif. la couleur)')
    cercle(25,110,15,'darkred','red')
    cercle(25,170,15,'darkblue','blue')
    cercle(25,230,15,'darkgrey','grey')
    cercle(25,290,15,'gold','yellow')
    cercle(25,350,15,'#BF00BF','#D900D9')
    rectangle(23,85,27,95,couleur='#752800', remplissage='#752800')
    rectangle(23,145,27,155,couleur='#752800', remplissage='#752800')
    rectangle(23,205,27,215,couleur='#752800', remplissage='#752800')
    rectangle(23,265,27,275,couleur='#752800', remplissage='#752800')
    rectangle(23,325,27,335,couleur='#752800', remplissage='#752800')
    attente_clic()
    

def choix_mode_jeu(L):
    """
    Interface de selection de mode de jeu.
    """
    while True:
        efface_tout()
        texte(185,20,'SNAKE','black','nw',"Purisa",50)
        rectangle(560,360,599,399,'black','#A9A9A9')
        rectangle(570,363,590,396,'#8D3500','#C74B00',3)
        cercle(585,380,3,'#C69803','#FFE100')
        rectangle(200,160,400,200,'black','#A9A9A9')
        rectangle(200,220,400,260,'black','#A9A9A9')
        rectangle(200,280,400,320,'black','#A9A9A9')
        rectangle(200,340,400,380,'black','#A9A9A9')
        texte(232,161,'Classique')
        texte(227,221,'Labyrinthe')
        texte(222,281,'Multiplayer')
        texte(240,341,'Multi-lab')
        mise_a_jour()
        x,y,z = attente_clic()
        if 560<=x<=600:
            if 360<=y<=400:
                break
        elif 200<=x<=400:
            if 160 <= y <= 200:
                touches = assigne_touches(1)
                ferme_fenetre()
                Points = classique(L,touches[0])
                ferme_fenetre()
                cree_fenetre(600,400)
            elif 220 <= y <= 260:
                touches = assigne_touches(1)
                ferme_fenetre()
                Points = labyrinthe(L,touches[0])
                ferme_fenetre()
                cree_fenetre(600,400)
            elif 280 <= y <= 320:
                L[7] = nombre_de_joueurs(L[7])
                if L[7] != 0:
                    touches = assigne_touches(L[7])
                    ferme_fenetre()
                    Points = multijoueurs(L,touches)
                    ferme_fenetre()
                    cree_fenetre(600,400)
            elif 340 <= y <= 380:
                L[7] = nombre_de_joueurs(L[7])
                if L[7] != 0:
                    touches = assigne_touches(L[7])
                    ferme_fenetre()
                    Points = multijoueurs_labyrinthe(L,touches)
                    ferme_fenetre()
                    cree_fenetre(600,400)

def choix_option(L):
    """
    Interface concernant les options.
    """
    while True:
        efface_tout()
        rectangle(200,100,400,140,'black','#A9A9A9')
        rectangle(200,160,400,200,'black','#A9A9A9')
        rectangle(200,220,400,260,'black','#A9A9A9')
        rectangle(200,280,400,320,'black','#A9A9A9')
        rectangle(200,340,400,380,'black','#A9A9A9')
        rectangle(560,360,599,399,'black','#A9A9A9')
        rectangle(570,363,590,396,'#8D3500','#C74B00',3)
        cercle(585,380,3,'#C69803','#FFE100')
        cercle(100,120,10,L[0],L[8])
        cercle(120,120,10,L[0],L[8])
        cercle(140,120,10,L[0],L[8])
        texte(240,100,'Couleur')
        diff = 'Difficulté : ' + str(L[1])
        if L[6] == 'Y':
            diff = 'Difficulté : hard'
        texte(217,165,diff,'black','nw','Purisa',20,'diff')
        vit = 'Vitesse : ' + str(L[2])
        texte(210,222,vit,'black','nw','Purisa',23,'vit')
        texte(220,280,'Taille écran')
        texte(240,340,'Torique',L[5])
        mise_a_jour()
        x,y,z=attente_clic()
        if 200<=x<=400:
            if 100<=y<=140:
                L[0],L[8] = modification_de_couleur(L[0],100)
            elif 160<=y<=200:
                L[1],L[6] = modification_difficulte(L[1],160,L[6])
            elif 220<=y<=260:
                L[2] = modification_vitesse(L[2],220)
            elif 280<=y<=320:
                L[3] = selection_taille_fenetre(L[3])
            elif 340<=y<=380:
                if L[4] == 'Y':
                    L[4] = 'N'
                    L[5] = 'red'
                else:
                    L[4] = 'Y'
                    L[5] = 'green'
        elif 560<=x<=600:
            if 360<=y<=400:
                return L

def modification_de_couleur(var,y):
    """
    Affiche deux boutons qui permettent de selectionner une couleur
    parmi la liste L ci-dessous.
    """
    for i in range(len(Couleurs)):      #Permet de savoir à quel valeur
        if L[i] == var:                 #de la liste la personne est en
            break                       #arrivant.
    while True:
        rectangle(410,y,437,y+17,'black','#A9A9A9')
        rectangle(410,y+23,437,y+40,'black','#A9A9A9')
        fleche(424,y+20,424,y+5,'black',2)
        fleche(424,y+30,424,y+35,'black',2)
        x2,y2,z2=attente_clic()
        if 410<=x2<=437:
            if y<=y2<=y+17:
                i += 1
            elif y+23<=y2<=y+40:
                i -=1
        else:
            return Couleurs[i],Couleurs2[i]
        if i >= 12:
            i = 0
        if i < 0:
            i = 11
        cercle(100,120,10,Couleurs[i],Couleurs2[i])
        cercle(120,120,10,Couleurs[i],Couleurs2[i])
        cercle(140,120,10,Couleurs[i],Couleurs2[i])

def fleches(var,y):
    """
    Récupère les coordonnées du clic facilement
    et modifie la valeur de la variable entrée.
    q"""
    x,y,z = attente_clic()
    if 410 <= x <= 437:
        if y <= y <= y+17:
            var += 1
        elif y+23 <= y <= y+40:
            var -= 1
    else:
        return var,False
    return var,True



def modification_difficulte(var,y,Hard):
    '''
    Affiche deux boutons permettant de choisir son mode de
    difficulté.
    '''
    a=True
    while a:
        if var >= 8:
            var = 8
        elif var <= 1:
            var = 1
        rectangle(410,y,437,y+17,'black','#A9A9A9')
        rectangle(410,y+23,437,y+40,'black','#A9A9A9')
        fleche(424,y+20,424,y+5,'black',2)
        fleche(424,y+30,424,y+35,'black',2)
        efface('diff')
        diff = 'Difficulté : ' + str(var)
        if var == 8:
            Hard = 'Y'
            diff = 'Difficulté : hard'
        else:
            Hard = 'N'
        texte(217,165,diff,'black','nw','Purisa',20,'diff')
        var,a = fleches(var,y)
    return var,Hard

def modification_vitesse(var,y):
    '''
    Affiche deux boutons permettant de choisir
    la vitesse de commencement.
    '''
    a=True
    while a:
        if var >= 30:
            var = 30
        elif var <= 5:
            var = 5
        rectangle(410,y,437,y+17,'black','#A9A9A9')
        rectangle(410,y+23,437,y+40,'black','#A9A9A9')
        fleche(424,y+20,424,y+5,'black',2)
        fleche(424,y+30,424,y+35,'black',2)
        efface('vit')
        vit = 'Vitesse : ' + str(var)
        texte(210,222,vit,'black','nw','Purisa',23,'vit')
        var,a = fleches(var,y)
    return var

def selection_taille_fenetre(L):
    '''
    Interface permettant de modifier la taille de la fenêtre.
    '''
    a = 240
    while True:
        efface_tout()
        rectangle(200,100,400,140,'black','#A9A9A9')
        rectangle(200,160,400,200,'black','#A9A9A9')
        rectangle(200,220,400,260,'black','#A9A9A9')
        rectangle(200,280,400,320,'black','#A9A9A9')
        rectangle(200,340,400,380,'black','#A9A9A9')
        texte(225,100,'Taille case')
        texte(220,160,'Petit terrain')
        texte(202,220,'Terrain moyen','black','nw','Purisa',23)
        texte(210,280,'Grand terrain')
        texte(220,340,'Personalisé')
        rectangle(560,360,599,399,'black','#A9A9A9')
        rectangle(570,363,590,396,'#8D3500','#C74B00',3)
        cercle(585,380,3,'#C69803','#FFE100')
        mise_a_jour()
        polygone([(110,a),(130,a+20),(150,a-20),(130,a+10),(110,a)],'#00E345','#00E307')
        x,y,z = attente_clic()
        if 200<=x<=400:
            if 100<=y<=140:
                L[0] = modification_taille_case(L[0],100)
            elif 160<=y<=200:
                a = 180
                L[1],L[2] = 15,10
            elif 220<=y<=260:
                a = 240
                L[1],L[2] = 40,30
            elif 280<=y<=320:
                a = 300
                L[1],L[2] = 60,50
            elif 340<=y<=380:
                a = 360
                L[1],L[2] = modification_largeur_hauteur(L[1],L[2],340)
        elif 560<=x<=600:
            if 360<=y<=400:
                return L

def modification_taille_case(var,y):
    '''
    Affiche deux boutons permettant de choisir
    la taille des cases.
    '''
    a=True
    while a:
        texte(450,105, str(var),'black','nw',"Purisa",24,'taille')
        rectangle(410,y,437,y+17,'black','#A9A9A9')
        rectangle(410,y+23,437,y+40,'black','#A9A9A9')
        fleche(424,y+20,424,y+5,'black',2)
        fleche(424,y+30,424,y+35,'black',2)
        var,a = fleches(var,y)
        if var >= 20:
            var = 20
        elif var <= 5:
            var = 5
        efface('taille')
    return var

def modification_largeur_hauteur(l,h,y):
    '''
    Affiche quatre bouttons permettant de modifier
    la taille de la fenêtre de jeu.
    '''
    a=True
    while a:
        rectangle(410,y,437,y+17,'black','#A9A9A9')
        rectangle(410,y+23,437,y+40,'black','#A9A9A9')
        fleche(424,y+20,424,y+5,'black',2)
        fleche(424,y+30,424,y+35,'black',2)
        rectangle(445,y,472,y+17,'black','#A9A9A9')
        rectangle(445,y+23,472,y+40,'black','#A9A9A9')
        fleche(459,y+20,459,y+5,'black',2)
        fleche(459,y+30,459,y+35,'black',2)
        texte(410,y-30, str(l),'black','nw',"Purisa",17,'l')
        texte(445,y-30, str(h),'black','nw',"Purisa",17,'h')
        l,h,a = double_fleches(l,h,y)
        if l >= 99:
            l = 99
        elif l <= 10:
            l = 10
        elif h <= 10:
            h = 10
        elif h >= 99:
            h = 99
        efface('h')
        efface('l')
    return l,h

def double_fleches(l,h,centre):
    '''
    Récupère les coordonnées du clic facilement
    et modifie la valeur des variables entrées. 
    '''
    x,y,z = attente_clic()
    if 410 <= x <= 437:
        if centre <= y<= centre+17:
            l += 1
        elif centre+23 <= y <= centre+40:
            l -= 1
    elif 445 <= x <= 472:
        if centre <= y <= centre+17:
            h += 1
        elif centre+23 <= y <= centre+40:
            h -= 1
    else:
        return l,h,False
    return l,h,True

def assigne_touches(nb_players):
    '''
    Prend une liste de touches par défaut et la modifie en fonction
    de ce que l'utilisateur entre
    '''
    touches = [['Up','Left','Down','Right'],['z','q','s','d'],['y','g','h','j'],['o','k','l','m']]
    for i in range(nb_players):
        touches[i] = modification_des_touches(touches[i],i)
    return touches

def att_touche():
    '''
    Fonction qui devrait être dans l'upemtk...
    '''
    while True:
        texte(130,60,'Appuyer sur une touche.')
        x,y,z = attente_clic_ou_touche()
        if z == 'Touche':
            return y

def modification_des_touches(touche_joueur,joueur):
    '''
    Permet d'assigner de nouvelles touches aux joueurs.
    '''
    while True:
        efface_tout()
        texte(250,20,('Joueur ' + str(joueur + 1)))
        Up = 'Aller vers le haut : ' + touche_joueur[0]
        Left = 'Aller vers la gauche : ' + touche_joueur[1]
        Down = 'Aller vers le bas : ' + touche_joueur[2]
        Right = 'Aller vers la droite : ' + touche_joueur[3]
        rectangle(110,100,490,140,'black','#A9A9A9')
        rectangle(110,160,490,200,'black','#A9A9A9')
        rectangle(110,220,490,260,'black','#A9A9A9')
        rectangle(110,280,490,320,'black','#A9A9A9')
        texte(130,100,Up)
        texte(130,160,Down)
        texte(130,220,Left)
        texte(130,280,Right)
        rectangle(200,340,400,380,'black','#A9A9A9')
        texte(250,341,'Valider')
        x,y,z = attente_clic()
        if 110 <= x <= 490:
            if 100 <= y <= 140:
                touche_joueur[0] = att_touche()
            elif 160 <= y <= 200:
                touche_joueur[2] = att_touche()
            elif 220 <= y <= 260:
                touche_joueur[1] = att_touche()
            elif 280 <= y <= 320:
                touche_joueur[3] = att_touche()
            if 200 <= x <= 400:
                if 340 <= y <= 380:
                    return touche_joueur

def nombre_de_joueurs(Nb):
    '''
    Permet de choisir son nombre de joueurs.
    '''
    while True:
        efface_tout()
        rectangle(200,100,400,140,'black','#A9A9A9')
        rectangle(200,160,400,200,'black','#A9A9A9')
        rectangle(200,220,400,260,'black','#A9A9A9')
        texte(230,100,'2 Joueurs')
        texte(230,160,'3 Joueurs')
        texte(230,220,'4 Joueurs')
        rectangle(560,360,599,399,'black','#A9A9A9')
        rectangle(570,363,590,396,'#8D3500','#C74B00',3)
        cercle(585,380,3,'#C69803','#FFE100')
        mise_a_jour()
        x,y,z = attente_clic()
        if 200<=x<=400:
            if 100<=y<=140:
                return 2
            elif 160<=y<=200:
                return 3
            elif 220<=y<=260:
                return 4
        elif 560<=x<=600:
            if 360<=y<=400:
                return 0

'''
Place maintenant à l'affcihage des 'objets' du jeu.
'''

def affiche_points(Points):
    '''
    Affiche les points (ou le gagnant) en fin de partie.
    '''
    while True:
        efface_tout()
        milieu = (L[3][1]*L[3][0])/2
        texte(milieu-115,50,'SNAKE','black','nw',"Purisa",50)
        texte(milieu-80,300,str(Points))
        texte(milieu-97,200,'GAME OVER')
        rectangle(200,400,400,440,'black','#A9A9A9')
        texte(235,402,'Continue')
        x,y,z = attente_clic()
        if 200 <= x <= 400:
            if 400 <= y <= 440:
                break

def case_vers_pixel(case):
    """
    Fonction recevant les coordonnées d'une case du plateau sous la forme
    d'un couple d'entiers (ligne, colonne) et renvoyant les coordonnées du
    pixel se trouvant au centre de cette case. Ce calcul prend en compte la
    taille de chaque case, donnée par la variable globale taille_case.
    """
    x, y = case
    return (x + .5) * L[3][0], (y + .5) * L[3][0]

def affiche_multi_serpent(Serpents,directions):
    '''
    Récupère la liste contenant les coordonnées des serpents et
    les affichent en fonction de leur couleur.
    '''
    Couleurs = ['green','blue','red','yellow','darkgreen','darkblue','darkred','gold']
    for i in range(4):
        if Serpents[i] != [None]:               #Verification que le serpent existe.
            affiche_serpent(Serpents[i],directions[i],Couleurs[i],Couleurs[i+4])

def affiche_serpent(Serpent,direction,coule='green',coule2='darkgreen'):
    '''
    Affiche tous les segments d'un serpent.
    '''
    for i in range(len(Serpent)):
        x, y = case_vers_pixel(Serpent[i])
        cercle(x, y, L[3][0]/2 + 1,couleur=coule2, remplissage=coule)
        if i == len(Serpent)-1:
            if direction[0] == 0:
                y += direction[1]*5
                b = 0
                a = 3
            else:
                x += direction[0]*5
                a = 0
                b = 3
            cercle(x+a,y+b,1.25,'black','black')
            cercle(x-a,y-b,1.25,'black','black')

def affiche_pommes(pommes):
    '''
    Affiche toutes les pommes contenue dans la liste.
    '''
    for x in pommes:
        affiche_pomme(x)


def affiche_pomme(pomme):
    '''
    Affiche une pomme à partir d'un couple d'entiers.
    '''
    x, y = case_vers_pixel(pomme)

    cercle(x, y, L[3][0]/2,
           couleur='darkred', remplissage='red')
    rectangle(x-2, y-L[3][0]*.4, x+2, y-L[3][0]*.7,
              couleur='#752800', remplissage='#752800')

def affiche_power_up(power_up):
    x,y = case_vers_pixel(power_up[0])
    cercle(x, y, L[3][0]/2,
           couleur=power_up[1][0], remplissage=power_up[1][1])
    rectangle(x-2, y-L[3][0]*.4, x+2, y-L[3][0]*.7,
              couleur='#752800', remplissage='#752800')

def affiche_murs(murs,couleur):
    '''
    Pareil que les pommes.
    '''
    for x in murs:
        affiche_mur(x,couleur)

def affiche_mur(mur,couleur):
    '''
    Affiche un mur.
    '''
    x, y = case_vers_pixel(mur)
    a = L[3][0]/2
    rectangle(x-a,y-a,x+a,y+a,couleur,couleur)

def limitation_de_vitesse(f):           #Limite la vitesse pour que ça reste jouable.
    if f > 40:
        return 40
    if f < 5:
        return 5
    return f

def pomme_aleatoire(Serpent,murs):
    '''
    Selectionne une case aléatoire et y dépose une pomme,
    en faisant attention que le serpent ne soit pas dessus.
    '''
    pomme = (randint(0,L[3][1]-1),randint(0,L[3][2]-1))
    if pomme in Serpent:
        pomme = pomme_aleatoire(Serpent,murs)
    if pomme in murs:
        pomme = pomme_aleatoire(Serpent,murs)
    return pomme

def manger_pomme(pommes,Point,Serpent,f,murs):
    '''
    Cherche sur quelle pomme le serpent a sa tête, ajoute un point
    au score et change l'emplacement de la pomme.
    '''
    Serpent.insert(0,Serpent[0])
    Serpent.insert(0,Serpent[0])
    for i in range(len(pommes)):
        if pommes[i] == Serpent[-1]:
            pommes[i] = pomme_aleatoire(Serpent,murs)
            return pommes,Point+1,Serpent,Serpent[:-3],limitation_de_vitesse(f+1)

def prendre_bonus(color,color2,power_up,Points,Serpent,f):
    '''
    Cherche sur quelle pomme le serpent a sa tête, ajoute un point
    au score et change l'emplacement de la pomme.
    '''
    power = power_up[1][0]
    if power == 'gold':
        return color,color2,(-1,-1),Points+1,Serpent,Serpent[:-3],limitation_de_vitesse(f+4)
    if power == 'darkgrey':
        return color,color2,(-1,-1),Points,Serpent,Serpent[:-3],limitation_de_vitesse(f-5)
    if power == 'darkblue':
        if len(Serpent)>3:
            Serpent.pop(0)
            Serpent.pop(0)
            Serpent.pop(0)
        return color,color2,(-1,-1),Points,Serpent,Serpent[:-3],f
    if power == '#BF00BF':
        i = randint(0,11)
        return Couleurs[i],Couleurs2[i],(-1,-1),Points,Serpent,Serpent[:-3],f

def murs_aleatoire(x,pommes):
    '''
    Place un mur aléatoirement sur le plateau.
    En faisant attention que ce ne soit ni sur une pomme,
    ni sur la ligne d'apparition du serpent. 
    '''
    mur = (randint(0,L[3][1]-1),randint(0,L[3][2]-1))
    if mur[0] == x or mur in pommes:
        mur = murs_aleatoire(x,pommes)
    return mur

def murs_aleatoire_multi():
    '''
    Place un mur aléatoirement sur le plateau.
    En faisant attention que ce ne soit pas la ligne
    d'apparition des serpents. 
    '''
    mur = (randint(0,L[3][1]-1),randint(0,L[3][2]-1))
    if mur[1] == int(L[3][2]/2) or mur[0] == int(L[3][1]/2):
        mur = murs_aleatoire_multi()
    return mur

def mouvement_aleatoire(Serpent,pommes,power_up):
    mvt_alea = [(1,0),(0,1),(-1,0),(0,-1)]
    a,b = mvt_alea[randint(0,3)]
    if (power_up[0]+a,power_up[1]+b) in pommes:
        return power_up
    if (power_up[0]+a,power_up[1]+b) in Serpent:
        return power_up
    if not(0 <= power_up[0]+a < L[3][1]):
        return power_up
    if not(0 <= power_up[1]+b < L[3][2]):
        return power_up
    return (power_up[0]+a,power_up[1]+b)

def change_direction(direction,touche,touches):
    '''
    Récupère la liste contenant les touches du joueur
    et assigne un direction en fonction de la touche
    appuyée.
    '''
    touche = te_retourne_pas(direction,touche,touches)
    if touche == touches[0]:
        return (0,-1),touche
    elif touche == touches[2]:
        return (0,1),touche
    elif touche == touches[1]:
        return (-1,0),touche
    elif touche == touches[3]:
        return (1,0),touche
    else:
        return direction,touche

def te_retourne_pas(direction,touche,touches):
    '''
    Empêche le serpent de revenir en arrière.
    Si le touche pressée est à l'opposé de sa direction,
    on 'ignore' la pression de la touche. 
    '''
    if touche == touches[0] and direction==(0,1):
        return touches[2]
    elif touche == touches[2] and direction==(0,-1):
        return touches[0]
    elif touche == touches[1] and direction==(1,0):
        return touches[3]
    elif touche == touches[3] and direction==(-1,0):
        return touches[1]
    else:
        return touche

def avance_serpent_avance(direction,Serpent):
    '''
    Ajoute la direction au serpent et enlève sa queue,
    puis modifie collision en conséquence.  
    '''
    Serpent.append((Serpent[-1][0]+direction[0],Serpent[-1][1]+direction[1]))
    Serpent.pop(0)
    return Serpent,Serpent[:-3]


def avancez_serpents_avancez(Serpents,directions):
    '''
    Ajoute la direction à chaque liste des serpents et renvoie une nouvelle
    liste de collision en fonction des serpents.
    (Multijoueur seulement)
    '''
    Collision = []
    for i in range(4):
        if Serpents[i] != [None]:
            Serpents[i] += [(Serpents[i][-1][0] + directions[i][0],Serpents[i][-1][1] + directions[i][1])]
            Collision += Serpents[i][:-1]
    return Serpents, Collision

def torique(Serpent):
    '''
    Renvoie les coordonnées modulo la taille de la fenêtre.
    '''
    x,y = Serpent[-1]
    return (x%L[3][1],y%L[3][2])

def sortie_d_ecran(Serpent):
    '''
    Vérifie que le serpent n'est pas sorti de l'écran.
    '''
    if Serpent != [None]:
        x,y = Serpent[-1]
        if x<0 or x>L[3][1]-1:
            return True
        if y<0 or y>L[3][2]-1:
            return True
    return False

def fin(en_jeu):
    '''
    Detecte si il reste plus de deux joueurs en vie ou pas.
    '''
    if en_jeu <= 1:
        return [None],(0,0),[''],'fin'
    return [None],(0,0),[''],''

def gagnant(Serpents):
    '''
    Renvoie le numéro du vainqueur.
    '''
    for i in range(len(Serpents)):
        if Serpents[i] != [None]:
            winner = 'J'+str(i+1)+' à gagné.'
            return winner

'''
Mode de jeu.
(Les modes de jeux labyrinthe et multijoueurs_labyrinthe auraient
pu être fusionné avec classique et multijoueurs mais le fait
de bien séparer chaque mode de jeu m'a plus emballé,
même si globalement c'est la même chose avec des murs)
'''

def classique(L,touches):
    '''
    Serpent avec des pommes qui grandit au fur et à mesure
    qu'il mange des pommes.
    '''
    '''
    Initialisation des variable.
    '''
    liste = L*1                             #Pour ne pas modifier la liste principale lors des changement de couleurs.
    larg = liste[3][0]*liste[3][1]
    haut = liste[3][0]*liste[3][2]
    cree_fenetre(larg,haut+40)              #Le +40 est la zone d'affichage du score.
    framerate = liste[2]
    direction = (0,-1)
    touch = touches[0]                      #touch et pas touche sinon il y a conflit avec la fonction touche.
    case = (int(liste[3][1]/2)+1, int(liste[3][2]/2)+1)
    Serpent = [(int(liste[3][1]/2)+1, int(liste[3][2]/2)+2)] * 4 + [case]
    Collision = [(int(liste[3][1]/2)+1, int(liste[3][2]/2)+2)] * 4
    pommes = []
    tor = liste[4]                          #Toricité de l'écran.
    for i in range(5):
        pommes += [pomme_aleatoire(Serpent,[])]
    power_up = [(-1,-1),['gray','white']]
    Points = 0
    abuse_pas = 0
    texte(larg/2 - 128,haut/2-18,"Cliquer sur l'écran",'black','nw',"Purisa",24,'text')
    attente_clic()
    Tps = time()
    
    '''
    Boucle principale.
    '''
    while True:
        efface_tout()
        """
        Affichage des objets du jeu.
        """
        ligne(0,haut+2,larg,haut+2,'black',2)
        temps_ecoule = float(int(10*(time() - Tps))/10)
        Temps = str(temps_ecoule)+'s'
        Temps_de_jeu = 'Temps de jeu : ' + Temps
        texte(larg-longueur_texte(Temps_de_jeu),haut,Temps_de_jeu)
        Score = 'Score : ' + str(Points)
        texte(2,haut+3,Score)
        affiche_pommes(pommes)
        affiche_power_up(power_up)
        affiche_serpent(Serpent,direction,liste[8],liste[0])
        mise_a_jour()


        ev = donne_evenement()
        ty = type_evenement(ev)
        
        if power_up[0]==(-1,-1):
            if randint(0,100*framerate/10) <= 2:
                abuse_pas = Points+1
                power_up = [pomme_aleatoire(Serpent,[]),Power_up[randint(0,3)]]
        else:
            if randint(0,10) > 8:
                power_up[0] = mouvement_aleatoire(Serpent,pommes,power_up[0])
            
        if Serpent[-1] in pommes:
            pommes,Points,Serpent,Collision,framerate = manger_pomme(pommes,Points,Serpent,framerate,[])
        if Serpent[-1] == power_up[0]:
            liste[0],liste[8],power_up[0],Points,Serpent,Collision,framerate = prendre_bonus(liste[0],liste[8],power_up,Points,Serpent,framerate)
        if Serpent[-1] in Collision:
            ty = 'Quitte'
        if ty == 'Quitte':
            Points = 'Score : '+ str(Points)
            affiche_points(Points)
            return Points
        
        elif ty == 'Touche':
            touch = touche(ev)
            direction,touch = change_direction(direction,touch,touches)

        Serpent,Collision = avance_serpent_avance(direction,Serpent)
        if tor == 'N':
            if sortie_d_ecran(Serpent):
                Points = 'Score : '+ str(Points)
                affiche_points(Points)
                return Points
        else:
            Serpent[-1] = torique(Serpent)
        sleep(1/framerate)

def labyrinthe(L,touches):
    '''
    Serpent avec des pommes qui grandit au fur et à mesure
    qu'il mange des pommes et ajoute des obstacles.

    Initialisation des variable.
    '''
    liste = L*1
    larg = liste[3][0]*liste[3][1]
    haut = liste[3][0]*liste[3][2]
    couleur_murs = '#7F7F7F'
    diff = liste[1]
    if diff == 8:
        couleur_murs = '#D9D9E6'
    direction = (0,-1)
    touch = 'Up'
    cree_fenetre(larg,haut+40)
    framerate = liste[2]
    case = (int(liste[3][1]/2)+1, int(liste[3][2]/2)+1)
    Serpent = [(int(liste[3][1]/2)+1, int(liste[3][2]/2)+2)] * 4 + [case]
    Collision = [(int(liste[3][1]/2)+1, int(liste[3][2]/2)+2)] * 4
    tor = liste[4]
    pommes = []
    murs = []
    for i in range(5):
        pommes += [pomme_aleatoire(Serpent,murs)]
    for i in range(int(liste[3][2]*liste[3][1]*diff*0.02)):
        murs += [murs_aleatoire(Serpent[-1][0],pommes)]
    Points = 0
    texte(larg/2 - 128,haut/2-18,"Cliquer sur l'écran",'black','nw',"Purisa",24,'text')
    attente_clic()
    power_up = [(-1,-1),['gray','white']]
    abuse_pas = 0
    Tps = time()
    '''
    Boucle principale.
    '''
    while True:
        efface_tout()
        ligne(0,haut+2,larg,haut+2,'black',2)
        temps_ecoule = float(int(10*(time() - Tps))/10)
        Temps = str(temps_ecoule)+'s'
        Temps_de_jeu = 'Temps de jeu : ' + Temps
        texte(larg-longueur_texte(Temps_de_jeu),haut,Temps_de_jeu)
        Score = 'Score : ' + str(Points)
        texte(2,liste[3][0]*liste[3][2]+3,Score)
        affiche_pommes(pommes)
        affiche_power_up(power_up)
        affiche_serpent(Serpent,direction)
        affiche_murs(murs,couleur_murs)
        mise_a_jour()
        ev = donne_evenement()
        ty = type_evenement(ev)
        if Serpent[-1] in pommes:
            pommes,Points,Serpent,Collision,framerate = manger_pomme(pommes,Points,Serpent,framerate,murs)
        if Serpent[-1] == power_up[0]:
            liste[0],liste[8],power_up[0],Points,Serpent,Collision,framerate = prendre_bonus(liste[0],liste[8],power_up,Points,Serpent,framerate)
        if power_up[0]==(-1,-1) and Points != abuse_pas:
            if randint(0,100*framerate/10) >= 2:
                abuse_pas = Points+1
                power_up = [pomme_aleatoire(Serpent,murs),Power_up[randint(0,3)]]
        else:
            if randint(0,10) > 8:
                power_up[0] = mouvement_aleatoire(Serpent,pommes,power_up[0])
        if Serpent[-1] in Collision:
            Points = 'Score : '+ str(Points)
            affiche_points(Points)
            return Points
        if Serpent[-1] in murs:
            Points = 'Score : '+ str(Points)
            affiche_points(Points)
            return Points
        
        elif ty == 'Touche':
            touch = touche(ev)
            direction,touch = change_direction(direction,touch,touches)

        Serpent,Collision = avance_serpent_avance(direction,Serpent)
        if tor == 'N':
            if sortie_d_ecran(Serpent):
                Points = 'Score : '+ str(Points)
                affiche_points(Points)
                return Points
        else:
            Serpent[-1] = torique(Serpent)
        sleep(1/framerate)

def multijoueurs(L,touches):
    '''
    Mode multijoueur (de 2 à 4 joueurs) avec des serpents
    de longueur infinie.
    '''
    cree_fenetre(L[3][0] * L[3][1],L[3][0] * L[3][2]+40)
    framerate = L[2]
    directions = [(1,0),(-1,0)]
    Serpents = [[(5, int(L[3][2]/2))] + [(6,int(L[3][2]/2))]] + [[(L[3][1]-5, int(L[3][2]/2))] + [(L[3][1]-6, int(L[3][2]/2))]] + [[None]] * 2
    Collision = Serpents[0][-2:-1]
    Collision += Serpents[1][-2:1]
    if L[7] >= 3:
        Serpents[2] = [(int(L[3][1]/2),5)] + [(int(L[3][1]/2),6)]
        directions.append((0,1))
        touch3 = touches[2][0]
        Collision.append(Serpents[2][-2:-1])
    if L[7] == 4:
        Serpents[3] = [(int(L[3][1]/2),L[3][2]-5)] + [(int(L[3][1]/2),L[3][2]-6)]
        directions.append((0,-1))
        touch4 = touches[3][0]
        Collision.append(Serpents[3][-2:-1])
    tor = L[4]
    touch = touches[0][3]
    speed_up = 0
    en_jeu = L[7]
    fin_de_jeu = ''
    texte(L[3][1]*L[3][0]/2 - 128,L[3][2]*L[3][0]/2-18,"Cliquer sur l'écran",'black','nw',"Purisa",24,'text')
    attente_clic()
    Tps = time()
    while True:
        efface_tout()
        ligne(0,L[3][0]*L[3][2]+2,L[3][0]*L[3][1],L[3][0]*L[3][2]+2,'black',2)
        temps_ecoule = float(int(10*(time() - Tps))/10)
        Temps = str(temps_ecoule)+'s'
        Score = 'Temps de jeu : ' + Temps
        texte(2,L[3][0]*L[3][2]+3,Score)
        affiche_multi_serpent(Serpents,directions)
        mise_a_jour()
        ev = donne_evenement()
        ty = type_evenement(ev)
        if ty == 'Touche':
            touch = touche(ev)
        for i in range(4):
            if Serpents[i] != [None]:
                if touch in touches[i]:
                    directions[i],touch = change_direction(directions[i],touch,touches[i])
        Serpents,Collision = avancez_serpents_avancez(Serpents,directions)
        speed_up+=1
        if speed_up == 5:
            framerate += 1
            speed_up = 0
        if tor == 'N':
            for i in range(len(Serpents)):
                if sortie_d_ecran(Serpents[i]):
                    en_jeu -= 1
                    Serpents[i],directions[i],touches[i],fin_de_jeu = fin(en_jeu)
        else:
            for i in range(4):
                if Serpents[i] != [None]:
                    Serpents[i][-1] = torique(Serpents[i])
        for i in range(4):
            if Serpents[i] != [None]:
                if Serpents[i][-1] in Collision:
                    en_jeu -= 1
                    Serpents[i],directions[i],touches[i],fin_de_jeu = fin(en_jeu)
                else:
                    for j in range(4):
                        if Serpents[j] != [None]:
                            if Serpents[i][-1] == Serpents[j][-1] and i!=j:
                                en_jeu -= 1
                                Serpents[i],directions[i],touches[i],fin_de_jeu = fin(en_jeu)
        if fin_de_jeu == 'fin':
            Vainqueur = gagnant(Serpents)
            affiche_points(Vainqueur)
            return Vainqueur
        sleep(1/framerate)

def multijoueurs_labyrinthe(L,touches):
    '''
    Mode multijoueur (de 2 à 4 joueurs) avec des serpents
    de longueur infinie avec des obstacles.
    '''
    couleur_murs = '#7F7F7F'
    diff = L[1]
    if diff == 8:
        couleur_murs = '#D9D9E6'
    cree_fenetre(L[3][0] * L[3][1],L[3][0] * L[3][2]+40)
    framerate = L[2]
    directions = [(1,0),(-1,0)]
    Serpents = [[(5, int(L[3][2]/2))] + [(6,int(L[3][2]/2))]] + [[(L[3][1]-5, int(L[3][2]/2))] + [(L[3][1]-6, int(L[3][2]/2))]] + [[None]] * 2
    Collision = Serpents[0][-2:-1]
    Collision += Serpents[1][-2:1]
    if L[7] >= 3:
        Serpents[2] = [(int(L[3][1]/2),5)] + [(int(L[3][1]/2),6)]
        directions.append((0,1))
        touch3 = touches[2][0]
        Collision.append(Serpents[2][-2:-1])
    if L[7] == 4:
        Serpents[3] = [(int(L[3][1]/2),L[3][2]-5)] + [(int(L[3][1]/2),L[3][2]-6)]
        directions.append((0,-1))
        touch4 = touches[3][0]
        Collision.append(Serpents[3][-2:-1])
    tor = L[4]
    touch = touches[0][3]
    Points = 0
    speed_up = 0
    en_jeu = L[7]
    fin_de_jeu = ''
    texte(L[3][1]*L[3][0]/2 - 128,L[3][2]*L[3][0]/2-18,"Cliquer sur l'écran",'black','nw',"Purisa",24,'text')
    attente_clic()
    murs = []
    Tps = time()
    for i in range(int(L[3][2]*L[3][1]*diff*0.02)):
        murs += [murs_aleatoire_multi()]
    while True:
        efface_tout()
        ligne(0,L[3][0]*L[3][2]+2,L[3][0]*L[3][1],L[3][0]*L[3][2]+2,'black',2)
        temps_ecoule = float(int(10*(time() - Tps))/10)
        Temps = str(temps_ecoule)+'s'
        Score = 'Temps de jeu : ' + Temps
        texte(2,L[3][0]*L[3][2]+3,Score)
        affiche_multi_serpent(Serpents,directions)
        affiche_murs(murs,couleur_murs)
        mise_a_jour()
        ev = donne_evenement()
        ty = type_evenement(ev)
        if ty == 'Touche':
            touch = touche(ev)
        for i in range(4):
            if Serpents[i] != [None]:
                if touch in touches[i]:
                    directions[i],touch = change_direction(directions[i],touch,touches[i])
        Serpents,Collision = avancez_serpents_avancez(Serpents,directions)
        speed_up+=1
        if speed_up == 5:
            framerate += 1
            speed_up = 0
        if tor == 'N':
            for i in range(len(Serpents)):
                if sortie_d_ecran(Serpents[i]):
                    en_jeu -= 1
                    Serpents[i],directions[i],touches[i],fin_de_jeu = fin(en_jeu)
        else:
            for i in range(4):
                if Serpents[i] != [None]:
                    Serpents[i][-1] = torique(Serpents[i])
        for i in range(4):
            if Serpents[i] != [None]:
                if Serpents[i][-1] in Collision:
                    en_jeu -= 1
                    Serpents[i],directions[i],touches[i],fin_de_jeu = fin(en_jeu)
                elif Serpents[i][-1] in murs:
                    en_jeu -= 1
                    Serpents[i],directions[i],touches[i],fin_de_jeu = fin(en_jeu)
                else:
                    for j in range(4):
                        if Serpents[j] != [None]:
                            if Serpents[i][-1] == Serpents[j][-1] and i!=j:
                                en_jeu -= 1
                                Serpents[i],directions[i],touches[i],fin_de_jeu = fin(en_jeu)
        if fin_de_jeu == 'fin':
            Vainqueur = gagnant(Serpents)
            affiche_points(Vainqueur)
            return Vainqueur
        sleep(1/framerate)

if __name__ == "__main__":
    cree_fenetre(600,400)
    menu_principal(L)
