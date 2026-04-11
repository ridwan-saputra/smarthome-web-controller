const endpoint = "your esp ip";

function setLamp(roomId) {
  const btn = document.getElementById(`btn-lamp-ruang${roomId}`);
  const img = document.getElementById(`img-lamp-ruang${roomId}`);

  fetch(endpoint + `/lamp/room${roomId}`, {
    method: "POST",
  })
    .then((response) => response.text())
    .then((result) => {
      if (result === "ON") {
        btn.style.backgroundColor = "red";
        img.src = "./assets/light-bulb-on.png";
        btn.innerText = "TURN OFF";
      } else {
        btn.style.backgroundColor = "#1f5a87";
        img.src = "./assets/light-bulb-off.png";
        btn.innerText = "TURN ON";
      }
    })
    .catch((error) => console.error("Error:", error));
}

function getLamp(roomId) {
  const btnLamp = document.getElementById(`btn-lamp-ruang${roomId}`);
  const imgLamp = document.getElementById(`img-lamp-ruang${roomId}`);

  fetch(endpoint + `/lamp/room${roomId}`, {
    method: "GET",
  })
    .then((response) => response.text()) // nanti ganti .json()
    .then((result) => {
      if (result == "ON") {
        btnLamp.style.backgroundColor = "red";
        imgLamp.src = "./assets/light-bulb-on.png";
        btnLamp.innerText = "TURN OFF";
      } else {
        btnLamp.style.backgroundColor = "#1f5a87";
        imgLamp.src = "./assets/light-bulb-off.png";
        btnLamp.innerText = "TURN ON";
      }
    })
    .catch((error) => console.error("Error:", error));
}

// Panggil saat halaman load untuk semua ruangan
getLamp(1);
getLamp(2);
getLamp(3);
getLamp(4);
