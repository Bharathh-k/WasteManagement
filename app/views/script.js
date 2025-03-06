const API_URL = "http://localhost:8080";

async function loadRequests() {
    const response = await fetch(`${API_URL}/wastepickups`);
    const data = await response.json();

    const list = document.getElementById("requestsList");
    list.innerHTML = "";

    data.wastePickups.forEach(request => {
        const li = document.createElement("li");
        li.innerHTML = `
            ID: ${request.id} - ${request.wasteType} at ${request.pickupLocation} 
            <b>Status:</b> ${request.status} 
            <button onclick="deleteRequest(${request.id})">Cancel</button>
        `;
        list.appendChild(li);
    });
}

document.getElementById("pickupForm").addEventListener("submit", async (e) => {
    e.preventDefault();

    const wasteType = document.getElementById("wasteType").value;
    const pickupLocation = document.getElementById("pickupLocation").value;
    const pickupDateTime = document.getElementById("pickupDateTime").value;
    const userName = document.getElementById("userName").value;

    const response = await fetch(`${API_URL}/wastepickuprequest`, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            wasteType, pickupLocation, pickupDateTime, userName
        })
    });

    if (response.ok) {
        alert("Request submitted successfully!");
        loadRequests();
    } else {
        alert("Failed to submit request.");
    }
});

document.getElementById("updateForm").addEventListener("submit", async (e) => {
    e.preventDefault();

    const updateId = document.getElementById("updateId").value;
    const newPickupDateTime = document.getElementById("updatePickupDateTime").value;
    const newStatus = document.getElementById("updateStatus").value;

    const response = await fetch(`${API_URL}/wastepickups/${updateId}`, {
        method: "PUT",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({
            ...(newPickupDateTime && { pickupDateTime: newPickupDateTime }),
            ...(newStatus && { status: newStatus })
        })
    });

    if (response.ok) {
        alert("Request updated successfully!");
        loadRequests();
    } else {
        alert("Failed to update request.");
    }
});

document.getElementById("deleteForm").addEventListener("submit", async (e) => {
    e.preventDefault();

    const deleteId = document.getElementById("deleteId").value;

    const response = await fetch(`${API_URL}/wastepickupdelete/${deleteId}`, {
        method: "DELETE"
    });

    if (response.ok) {
        alert("Request deleted successfully!");
        loadRequests();
    } else {
        alert("Failed to delete request.");
    }
});

async function updateStatusAutomatically() {
    await fetch(`${API_URL}/wastepickups`);
    loadRequests();
}

setInterval(updateStatusAutomatically, 60000); // Check every minute
window.onload = loadRequests;
