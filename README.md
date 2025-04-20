# 🚜 AgroBot : Autonomous Hybrid Vehicle Robot Sprayer Otomatis untuk Pengendalian Agriculture Berbasis Watchdog System Guna Memitigasi Kegagalan Panen


## 📘 Deskripsi Proyek
**AgroBot** merupakan robot hybrid otomatis yang berfungsi sebagai sprayer tanaman di area pertanian. Didesain untuk beroperasi di lingkungan agriculture, sistem ini dilengkapi dengan **Watchdog System** untuk mengantisipasi kegagalan sistem selama operasi. AgroBot bertujuan meminimalisir potensi gagal panen dengan pengendalian hama dan penyakit tanaman secara cerdas, efisien, dan terintegrasi.

---

## 🎓 Mata Kuliah
- **[Pemrograman Kontroller]** – Program Studi Teknik Instrumentasi
- Dosen Pengampu: [Ahmad Radhy, S.Si., M.Si]

---

## 👨‍💻 Anggota Kelompok
| Nama | NIM | 
|------|-----|
| [Andik Putra Nazwana] | [2042231010] | 
| [Akhmad Maulvin Nazir Zakaria] | [2042231028] | 
| [Rany Surya Oktavia] | [2042231060] | 


---

## ⚙️ Fitur Utama
- ✅ Navigasi berbasis Wireless Controller
- ✅ Penyemprotan tanaman secara otomatis dan adaptif
- ✅ Sistem Watchdog: restart otomatis jika terjadi crash sistem
- ✅ Pemantauan status sistem secara real-time
- ✅ Efisiensi konsumsi daya dan air

---

## 🛠️ Teknologi dan Perangkat
- Mikrokontroler STM32F446RE dan STM32F103C8T6 
- Sensor DHT11 dan Soil Moisture Sensor
- Motor DC dengan driver L298N
- Sistem Watchdog internal & eksternal
- Framework: STM32CubeMX / Keil Uvision
- Bahasa: C
  
---

## 📚 Tutorial Setup Program Robot
- Pada halaman awal pilih Start my project from ST Board.  
  ![](DOKUMENTASI_CONTROLLER/Screenshot%20(43).png)
- Pada bagian comercial part number pilih STM32F446RE dan klik Strart Project.  
  ![](DOKUMENTASI_ROBOT/Screenshot%20(56).png)
- Pada System Core klik Sys, atur debug ke Serial Wire  
  ![](DOKUMENTASI_ROBOT/Screenshot%20(45).png)
- Pada bagian RCC, atur High Speed Clock(HSE) dan Low Speed Clock (LSE) Crystal/Ceramic Resonator  
  ![](DOKUMENTASI_ROBOT/Screenshot%20(46).png)
- Pada GPIO, atur PA5 dan PC3 sebagai GPIO Output.  
  ![](DOKUMENTASI_ROBOT/Screenshot%20(47).png)
- Pada ANALOG, aktifkan ADC3 channel IN12. Pada Parameter Settings aktifkan Contonous Conversion Mode.   
  ![](DOKUMENTASI_ROBOT/Screenshot%20(48).png)
- Pada TIMER, aktifkan TIM2 CH1 untuk Servo, TIM3 CH1 untuk DHT11, TIM10 CH1 untuk motor 1, TIM11 CH1 untuk motor 2, TIM12 CH1 untuk motor 3 dan CH2 untuk motor 4.
  ![](DOKUMENTASI_ROBOT/Screenshot%20(49).png)
  ![](DOKUMENTASI_ROBOT/Screenshot%20(50).png)
  ![](DOKUMENTASI_ROBOT/Screenshot%20(51).png)
  ![](DOKUMENTASI_ROBOT/Screenshot%20(52).png)
- Pada Conectivity, aktifkan SPI1 dan atur ke Full Duplex Slave dan aktifkan USART2 Asynchronus Mode.
  ![](DOKUMENTASI_Robot/Screenshot%20(53).png) 
  ![](DOKUMENTASI_Robot/Screenshot%20(54).png)
- Pada Clock Configuration tidak perlu diubah dan biarkan secara default.   
  ![](DOKUMENTASI_Robot/Screenshot%20(55).png)
- Pada Project Manager, Beri nama project dan atur Toolchain jadi MDK ARM, kemudian klik generate code.   
  ![](DOKUMENTASI_ROBOT/Screenshot%20(57).png)
- Setelah itu edit program pada main.c

---

## 📚 Tutorial Setup Program Controller
- Pada halaman awal pilih Start my project from MCU.  
  ![](DOKUMENTASI_CONTROLLER/Screenshot%20(43).png)
- Pada bagian comercial part number pilih STM32F103C8T6 dan klik Strart Project.  
  ![](DOKUMENTASI_CONTROLLER/Screenshot%20(44).png)
- Pada System Core klik Sys, atur debug ke Serial Wire  
  ![](DOKUMENTASI_CONTROLLER/Screenshot%20(24).png)
- Pada bagian RCC, atur High Speed Clock(HSE) Crystal/Ceramic Resonator  
  ![](DOKUMENTASI_CONTROLLER/Screenshot%20(25).png)
- Pada bagian IWDG, klik activated dan atur prescaler dengan nilai 32 dan IWDG counter value 4095.  
  ![](DOKUMENTASI_CONTROLLER/Screenshot%20(26).png)
- Pada GPIO, atur PA4,PB12,PB13,PB14,PB15 sebagai GPIO Output dan PB3 PB4 sebagai GPIO Input.  
  ![](DOKUMENTASI_CONTROLLER/Screenshot%20(27).png)
- Pada ANALOG, aktifkan ADC1 channel IN0 dan IN1. Pada Parameter Settings aktifkan Contonous Conversion Mode.   
  ![](DOKUMENTASI_CONTROLLER/Screenshot%20(28).png)
- Pada Conectivity, aktifkan SPI1 dan atur ke Full Duplex Master dan atur presclaer baud rate ke 16.   
  ![](DOKUMENTASI_CONTROLLER/Screenshot%20(30).png)
- Pada Clock Configuration, atur ke HSE dan ubah HCLK jadi 72MHz.   
  ![](DOKUMENTASI_CONTROLLER/Screenshot%20(31).png)
- Pada Project Manager, Beri nama project dan atur Toolchain jadi MDK ARM, kemudian klik generate code.   
  ![](DOKUMENTASI_CONTROLLER/Screenshot%20(33).png)
- Setelah terbuka Keil, klik kanan Aplication/User/Core dan masukkan library NRF2L401.c yang telah dibuat.   
  ![](DOKUMENTASI_CONTROLLER/Screenshot%20(34).png)
- Pada option for target, atur ARM Compiler menjadi Use Default Compiler Version 6.   
  ![](DOKUMENTASI_CONTROLLER/Screenshot%20(35).png)
- Setelah itu edit program pada main.c
  
---

## 🖼️ Dokumentasi dan Demo
📷 Lihat foto dan video demo di folder [`/media`](./media)  
📹 [Link ke YouTube Demo](#) *(opsional, jika ada)*

---

## 📌 Saran untuk Pengembangan Selanjutnya
- Integrasi dengan IoT dashboard untuk monitoring dari jarak jauh
- Penambahan AI untuk klasifikasi penyakit tanaman
- Manajemen energi dengan panel surya

---

## 🌱 Lisensi
Agrobot_TEKINS23_ITS

---

> 🚀 “Teknologi bukan hanya alat, tapi jembatan menuju masa depan pangan yang lebih cerdas.”  
> — Tim AgroBot

