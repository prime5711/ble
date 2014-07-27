XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
X   Artwork and documentation done by:                         X
X                                                              X
X           TEXAS INSTRUMENTS LPRF                             X
X                                                              X
X   Address: Gaustadall�en 21, 0349 OSLO, Norway               X
X   Phone..: (+47) 22 95 85 44                                 X
X   Web....: www.ti.com/lprf                                   X
X                                                              X
XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

PCB NAME: CC2541 Keyfob
REVISION: 1.4.0
DATE:     2012-08-30

PCB DESCRIPTION:4 LAYER PCB 1.6 MM
      Copper        1   35 um
      Dielectric  1-2   0.35 mm (e.g. 2x Prepreg 7628 AT05 47% Resin)
      Copper        2   18 um
      Dielectric  2-3   0.76 mm (4 x 7628M 43% Resin)
      Copper        3   18 um
      Dielectric  3-4   0.35 mm (e.g. 2x Prepreg 7628 AT05 47% Resin)
      Copper        4   35 um

  DE104iML or equivalent substrate (Resin contents around 45%, which gives Er=4.42@2.4GHz, TanD=0.016)
  Dimensions in mil (0.001 inch)
  DOUBLE SIDE SOLDER MASK,
  DOUBLE SIDE SILKSCREEN,
  8 MIL MIN TRACE WIDTH AND 8 MIL MIN ISOLATION.
    
ASSEMBLY:   LABEL CARD WITH "CC2541Keyfob 1.4.0"

FILE: CC2541Keyfob_Reference_Design.ZIP PACKED WITH WinZIP containing 
                 
FILE NAME                       DESCRIPTION                                     FILE TYPE

PCB MANUFACTURING FILES:
L1.SPL                          LAYER 1 COMPONENT SIDE/POSITIVE                 EXT. GERBER
L2.SPL                          LAYER 2 POSITIVE                                EXT. GERBER
L3.SPL                          LAYER 3 POSITIVE                                EXT. GERBER
L4.SPL                          LAYER 4 SOLDER SIDE/POSITIVE                    EXT. GERBER
STOPCOMP.SPL                    SOLDER MASK COMPONENT SIDE/NEGATIVE             EXT. GERBER
STOPSOLD.SPL                    SOLDER MASK SOLDER SIDE/NEGATIVE                EXT. GERBER
SILKCOMP.SPL                    SILKSCREEN COMPONENT SIDE/POSITIVE              EXT. GERBER
SILKSOLD.SPL                    SILKSCREEN SOLDER SIDE/POSITIVE                 EXT. GERBER
GERBER.REP                      DRILL and NC DRILL REPORT                       ASCII
DRILL.SPL                       DRILL/MECHANICAL DRAWING                        EXT. GERBER
NCDRILL.SPL                     NC DRILL THROUGH HOLE                           EXCELLON            

PCB ASSEMBLY FILES:
CC2541Keyfob_PARTLIST.XLS       PART LIST                                       EXCEL
P&PCOMP.REP                     PICK AND PLACE COORDINATES, COMPONENT SIDE      ASCII
P&PSOLD.REP                     PICK AND PLACE COORDINATES, SOLDER SIDE         ASCII
PASTCOMP.SPL                    SOLDER PASTE COMPONENT SIDE                     EXT. GERBER
PASTSOLD.SPL                    SOLDER PASTE SOLDER SIDE                        EXT. GERBER
ASSYCOMP.SPL                    ASSEMBLY DRAWING COMPONENT SIDE                 EXT. GERBER
ASSYSOLD.SPL                    ASSEMBLY DRAWING SOLDER SIDE                    EXT. GERBER

PDF FILES:
CC2541Keyfob_SCHEMATIC.PDF      CIRCUIT DIAGRAM
CC2541Keyfob_LAYOUT.PDF         LAYOUT DIAGRAM

CADSTAR FILES:
CC2541Keyfob.SCM                CADSTAR SCHEMATIC FILE
CC2541Keyfob.PCB                CADSTAR LAYOUT FILE

README.TXT                      THIS FILE                                       ASCII

END.

Release history
--------------------------------------------------------------------------------------------------------------
1.0.0 : Initial release. Based on CC2540_MiniDK_1.2.0.
1.1.0 : Change 32.768kHz crystal. SCL/SDA now come out to 'Test' pin header. Added diode to prevent charging of battery by CC Debugger
1.2.0 : Changes to accelerometer supply scheme, cleaning up top silk and bottom silk
1.3.0 : Reverse polarity of fail safe diode, moved components away from buzzer
1.4.0 : Replace D1 diode with 0 ohm resistor


