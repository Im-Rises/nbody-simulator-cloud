#!/bin/bash
export DISPLAY=:0  # Définit le numéro de l'affichage virtuel (peut être différent selon votre système)
xvfb-run -a -s "-screen 0 1280x1024x24" ./NBodyGraphics/NBodyGraphics