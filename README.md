# ASP_Oswald_Leandro

## Höhenabfrage in UE5 – Schritt für Schritt 

### 1) Alle Referenzen prüfen

#### TerrainReferenceActor
- **Im Viewport auswählen**  
- `Landscape`  
  → Referenz auf das Landscape im Level setzen
  
#### VoxelGridBaker Actor 
- **Im Viewport auswählen**  
- `Terrain Ref`  
  → Referenz auf den Actor, der das Terrain/Landscape repräsentiert (TerrainRefernceActor)
- `HeightCache`  
  → DataAsset vom Typ `VoxelHeightCache`
- `GridConfig`  
  → DataAsset vom Typ `VoxelGridConfig`

#### HeightQueryProbeActor
- **Im Viewport auswählen**  
- `GridBaker`  
  → Referenz auf den GridBaker Actor im Level
- `HeightCache`  
  → **gleiches** `VoxelHeightCache` Asset wie beim GridBaker

---

### 2) Grid backen
- **VoxelGridBaker** im Viewport auswählen
- Im Details-Panel:
  - **BuildGrid** ausführen
  - **BakeMaxHeight** ausführen
- Ergebnis:
  - HeightCache wird gefüllt (Grid-Daten + Max-Höhen pro Zelle)

---

### 3) HeightQueryProbeActor 
- **HeightQueryProbeActor** im Viewport auswählen
- Actor **frei im Level verschieben** (X/Y-Pos ist entscheidend, Z-Pos ist egal)
- Die aktuelle World-Position des Actors bestimmt,
  **für welche Stelle im Terrain die Höhe abgefragt wird**

---

### 4) Höhenabfrage ausführen
- **HeightQueryProbeActor** auswählen
  - **QueryHeightAtMyLocation** ausführen:

**Was passiert intern:**
- Actor-Position → World XY
- World XY → Grid-Zelle
- Höhe aus dem HeightCache lesen
- Ausgabe im Log (World-Z in cm / m, optional ASL)

---

### 5) Ergebnis prüfen
- Output Log zeigt:
  - WorldXY
  - Grid-Zelle (X/Y)
  - Gefundene Höhe


# Lerntagebuch – ASP

## Projektstart & Vorbereitung
**Zeitraum:** ab 12.11.2025

**Tätigkeiten:**
- Projektstart
- Repository erstellt
- Unreal Engine 5 Projekt angelegt
- Grobplanung der Arbeitspakete

**Gelernt:**
- Projektstrukturierung
- Aufteilung in technische Teilbereiche

---

## Recherche
**Zeitraum:** 14.11.2025 – 06.01.2026

**Tätigkeiten:**
- Recherche zu Geodaten und Höhenmodellen
- Analyse von swissALTI3D
- Einarbeitung in QGIS
- Recherche zu Heightmaps in Unreal Engine 5
- Grundlagen zu Grid- und Voxel-Strukturen

**Gelernt:**
- Geodatenformate und Auflösungen
- Heightmaps und Höhenwerte
- Unterschiede reale Welt vs. Game Engine
- Rasterbasierte Datenstrukturen

---

## QGIS Tests & erste Datenimporte
**Zeitraum:** 23.11.2025 – 15.12.2025

**Tätigkeiten:**
- Import von Höhendaten in QGIS
- Zusammenführen mehrerer Tiles
- Berechnung passender Auflösungen
- Export als 16-Bit Heightmap
- Erste Test-Heightmaps

**Gelernt:**
- Praktischer Umgang mit QGIS
- Bedeutung von Bit-Tiefe
- Vorbereitung von Daten für Game Engines
- Typische Export-Fehler

---

## Terrain-Import in Unreal Engine
**Zeitraum:** 19.12.2025 – 27.12.2025

**Tätigkeiten:**
- Mehrere Terrain-Import-Tests
- Landscape-Erstellung in Unreal Engine
- Anpassung der X/Y-Skalierung
- Anpassung der Z-Skalierung
- Material- und Sichttests

**Gelernt:**
- Heightmap-Import in Unreal Engine
- Zusammenhang Auflösung und Terrain-Grösse
- Typische Import-Fehler

---

## Voxel-Struktur & Höhenabfragen
**Zeitraum:** 29.12.2025 – 09.01.2026

**Tätigkeiten:**
- Aufbau einer Grid- / Voxel-Struktur
- Implementierung von Höhenabfragen
- Speicherung von Maximalhöhen pro Zelle
- Einführung eines Sea-Level-Offsets
- Code-Kommentierung

**Gelernt:**
- Grid-basierte Datenstrukturen
- Trennung von Daten und Logik
- Höhenabfragen auf Terrain-Basis
- Datenorientiertes Arbeiten

---

## Optimierung & Bugfixing
**Zeitraum:** 09.01.2026 – 15.01.2026

**Tätigkeiten:**
- Bugfixing der Höhenberechnung
- Überprüfung von Debug-Ausgaben
- Validierung der Höhenwerte
- Performance-Tests

**Gelernt:**
- Systematisches Debugging
- Überprüfung von Berechnungsergebnissen
- Performance-Bewusstsein

---

## E-Learning & Abschluss
**Zeitraum:** 17.01.2026 – 01.02.2026

**Tätigkeiten:**
- Strukturierung des E-Learnings
- Auswahl relevanter Inhalte
- Vereinfachung technischer Erklärungen
- Vorbereitung der Abgabe

**Gelernt:**
- Technische Inhalte verständlich erklären
- Reduktion auf das Wesentliche
- Dokumentation eines technischen Workflows

---

## Finalisierung, Dokumentation & Reflexion
**Zeitraum:** 01.02.2026 – 18.02.2026

**Tätigkeiten:**
- Fertigstellung des E-Learnings (Inhalt überarbeitet und strukturiert)
- Erstellung des Leaflets
- Ausformulierung der selbstkritischen Reflexion
- Überarbeitung der Dokumentation
- Vorbereitung der finalen Abgabe (Repository, Struktur, Kontrolle)

**Gelernt:**
- Inhalte zielgerichtet zusammenfassen
- Unterschied zwischen technischer Umsetzung und didaktischer Aufbereitung
- Eigene Arbeit kritisch analysieren
- Reflexion von Stärken und Schwächen im Projektverlauf
- Bedeutung sauberer Abschlusskontrolle vor Abgabe
