# CPU Scheduling Simulation

This project is a **C-based simulation** of a CPU scheduling system, implementing process management and priority-based scheduling using a **min-heap structure**. It is designed as part of coursework for the **Computer Engineering Faculty at Istanbul Technical University**.

## 🧠 Features

- Dynamic process management
- Min-heap based priority scheduling
- Simulation of real-world CPU scheduler behavior
- Modular code structure for clarity and extensibility
- Performance-oriented implementation using custom data structures

## 📚 Project Origin

Developed as an assignment for the **Computer Engineering Department** at **Istanbul Technical University (ITU)**.

## 🗂️ File Structure
````
├── Makefile               # Build system
├── README.md              # Project description
├── include/               # Header files
│   ├── min_heap.h
│   ├── process.h
│   └── scheduler.h
├── lib/                   # External libraries
│   └── munit/             # Munit test framework
├── src/                   # Source files
│   ├── main.c
│   ├── min_heap.c
│   ├── process.c
│   └── scheduler.c
├── tests/                 # Unit tests
│   ├── tests.c
│   ├── test_min_heap.c / .h
│   └── test_scheduler.c / .h
````

## ⚙️ How to Build

```bash
make
```
## ▶️ How to Run

```bash
./bin/scheduler
```
# 🔎 Example Features You Can Add
	•	Time quantum simulation for Round Robin
	•	IO wait handling
	•	Gantt chart visualization via terminal or file output
Note: This project was developed as part of an academic assignment under the **Faculty of Computer and Informatics Engineering** at **Istanbul Technical University (ITU)**.
