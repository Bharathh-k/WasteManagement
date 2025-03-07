Waste Pickup Management System

A modern waste pickup request system built with C++ (Crow Web Framework) and a responsive web frontend built as an assignment for Object Oriented Analysis and Design

Install Dependencies
```
sudo apt update
sudo apt install g++ cmake libboost-all-dev
```

Clone the Repository
```
git clone https://github.com/Bharathh-k/WasteManagement.git

```

Navigate to Project Directory
```
cd app
```

Install Crow (if not already included):
```
git clone https://github.com/CrowCpp/Crow.git
```

Compile the Server
```
g++ -o server main.cpp -I Crow/include -lboost_system -lpthread -std=c++17
```

Run the Server
```
./server
```
