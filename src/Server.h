#ifndef SERVER_H
#define SERVER_H

#include "httplib.h"
#include "Biblioteca.h"
#include "Fisiere.h"
#include "AuthManager.h"
#include "CarteFictiune.h"
#include "CarteTehnica.h"
#include "CarteEducativa.h"
#include "CarteCopii.h"
#include "MaterialeReferinta.h"
#include "TipuriSpeciale.h"
#include "UtilizatorBasic.h"
#include "UtilizatorStudent.h"
#include "UtilizatorStaff.h"
#include <string>
#include <sstream>
#include <map>
#include <thread>
#include <cstdlib>

using std::string;

// ===================================================================
// Helper JSON simplu (fara dependente externe)
// ===================================================================
namespace JSON
{
    static string esc(const string& s)
    {
        string r;
        for (char c : s)
        {
            if (c == '"')  r += "\\\"";
            else if (c == '\\') r += "\\\\";
            else if (c == '\n') r += "\\n";
            else if (c == '\r') r += "\\r";
            else if (c == '\t') r += "\\t";
            else r += c;
        }
        return r;
    }

    static string str(const string& key, const string& val)
    { return "\"" + key + "\":\"" + esc(val) + "\""; }

    static string num(const string& key, double val)
    {
        std::ostringstream oss;
        oss << "\"" << key << "\":" << val;
        return oss.str();
    }

    static string num(const string& key, int val)
    {
        return "\"" + key + "\":" + std::to_string(val);
    }

    static string boolean(const string& key, bool val)
    { return "\"" + key + "\":" + (val ? "true" : "false"); }
}

// ===================================================================
// Sesiuni active (token -> idUtilizator)
// ===================================================================
static std::map<string, string> sesiuniActive;

static string genToken(const string& id)
{
    std::size_t h = std::hash<string>{}(id + std::to_string(std::time(nullptr)));
    std::ostringstream oss;
    oss << std::hex << h;
    return oss.str();
}

static string getIdDinToken(const httplib::Request& req)
{
    auto it = req.headers.find("Authorization");
    if (it == req.headers.end()) return "";
    string token = it->second;
    if (token.substr(0, 7) == "Bearer ") token = token.substr(7);
    auto sit = sesiuniActive.find(token);
    if (sit == sesiuniActive.end()) return "";
    return sit->second;
}

// ===================================================================
// HTML - Interfata Dark Academia
// ===================================================================
static string getHTML()
{
    return R"HTML(<!DOCTYPE html>
<html lang="ro">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1.0">
<title>Biblioteca Universitara Suceava</title>
<style>
  @import url('https://fonts.googleapis.com/css2?family=Playfair+Display:ital,wght@0,400;0,700;1,400&family=Lora:ital,wght@0,400;0,600;1,400&family=EB+Garamond:ital,wght@0,400;0,600;1,400&display=swap');

  :root {
    --bg:        #0d0b08;
    --bg2:       #151210;
    --bg3:       #1e1a15;
    --border:    #3a2e20;
    --gold:      #c9a84c;
    --gold2:     #e8c97a;
    --cream:     #e8dfc8;
    --cream2:    #d4c9a8;
    --text:      #c8bfa8;
    --text2:     #9a8e78;
    --red:       #8b2020;
    --green:     #2a5c3a;
    --green2:    #4a8c5a;
    --shadow:    0 4px 24px rgba(0,0,0,0.7);
  }

  * { box-sizing: border-box; margin: 0; padding: 0; }

  body {
    background: var(--bg);
    color: var(--text);
    font-family: 'Lora', serif;
    min-height: 100vh;
    background-image:
      radial-gradient(ellipse at 20% 50%, rgba(60,40,10,0.15) 0%, transparent 60%),
      radial-gradient(ellipse at 80% 20%, rgba(40,25,5,0.1) 0%, transparent 50%);
  }

  /* ---- LOGIN ---- */
  #login-page {
    min-height: 100vh;
    display: flex;
    align-items: center;
    justify-content: center;
    background-image: url('https://images.unsplash.com/photo-1481627834876-b7833e8f5570?w=1600&q=80');
    background-size: cover;
    background-position: center;
  }
  #login-page::before {
    content: '';
    position: fixed;
    inset: 0;
    background: rgba(8,6,3,0.82);
    z-index: 0;
  }
  .login-box {
    position: relative;
    z-index: 1;
    background: rgba(21,18,13,0.95);
    border: 1px solid var(--border);
    border-top: 2px solid var(--gold);
    padding: 48px 52px;
    width: 420px;
    box-shadow: var(--shadow), 0 0 60px rgba(201,168,76,0.08);
  }
  .login-box h1 {
    font-family: 'Playfair Display', serif;
    color: var(--gold);
    font-size: 1.6rem;
    text-align: center;
    margin-bottom: 6px;
    letter-spacing: 0.05em;
  }
  .login-box .subtitle {
    text-align: center;
    color: var(--text2);
    font-size: 0.8rem;
    font-style: italic;
    margin-bottom: 36px;
    letter-spacing: 0.1em;
  }
  .ornament {
    text-align: center;
    color: var(--gold);
    font-size: 1.2rem;
    margin-bottom: 28px;
    opacity: 0.6;
  }

  /* ---- FORM ---- */
  .form-group { margin-bottom: 20px; }
  .form-group label {
    display: block;
    color: var(--text2);
    font-size: 0.75rem;
    letter-spacing: 0.12em;
    text-transform: uppercase;
    margin-bottom: 8px;
  }
  .form-group input, .form-group select, .form-group textarea {
    width: 100%;
    background: var(--bg3);
    border: 1px solid var(--border);
    color: var(--cream);
    padding: 10px 14px;
    font-family: 'Lora', serif;
    font-size: 0.9rem;
    outline: none;
    transition: border-color 0.2s;
  }
  .form-group input:focus, .form-group select:focus {
    border-color: var(--gold);
  }
  .form-group select option { background: var(--bg3); }

  /* ---- BUTTONS ---- */
  .btn {
    display: inline-block;
    padding: 10px 24px;
    font-family: 'Lora', serif;
    font-size: 0.85rem;
    letter-spacing: 0.08em;
    cursor: pointer;
    border: none;
    transition: all 0.2s;
    text-transform: uppercase;
  }
  .btn-gold {
    background: var(--gold);
    color: var(--bg);
    font-weight: 600;
  }
  .btn-gold:hover { background: var(--gold2); }
  .btn-outline {
    background: transparent;
    border: 1px solid var(--gold);
    color: var(--gold);
  }
  .btn-outline:hover { background: rgba(201,168,76,0.1); }
  .btn-danger {
    background: var(--red);
    color: var(--cream);
  }
  .btn-danger:hover { background: #a02828; }
  .btn-full { width: 100%; }

  /* ---- LAYOUT ---- */
  #app { display: none; }
  .layout { display: flex; min-height: 100vh; }

  /* ---- SIDEBAR ---- */
  .sidebar {
    width: 260px;
    min-height: 100vh;
    background: var(--bg2);
    border-right: 1px solid var(--border);
    display: flex;
    flex-direction: column;
    position: fixed;
    top: 0; left: 0; bottom: 0;
    z-index: 100;
  }
  .sidebar-header {
    padding: 28px 24px 20px;
    border-bottom: 1px solid var(--border);
  }
  .sidebar-header h2 {
    font-family: 'Playfair Display', serif;
    color: var(--gold);
    font-size: 1.1rem;
    line-height: 1.4;
  }
  .sidebar-header .user-info {
    margin-top: 10px;
    font-size: 0.75rem;
    color: var(--text2);
  }
  .sidebar-header .user-role {
    display: inline-block;
    margin-top: 4px;
    padding: 2px 8px;
    border: 1px solid var(--gold);
    color: var(--gold);
    font-size: 0.65rem;
    letter-spacing: 0.1em;
    text-transform: uppercase;
  }
  .nav-section {
    padding: 16px 0;
    border-bottom: 1px solid var(--border);
  }
  .nav-section-title {
    padding: 0 24px 8px;
    font-size: 0.65rem;
    letter-spacing: 0.15em;
    text-transform: uppercase;
    color: var(--text2);
  }
  .nav-item {
    display: flex;
    align-items: center;
    gap: 12px;
    padding: 10px 24px;
    color: var(--text2);
    cursor: pointer;
    font-size: 0.85rem;
    transition: all 0.15s;
    border-left: 2px solid transparent;
  }
  .nav-item:hover { color: var(--cream); background: rgba(201,168,76,0.05); }
  .nav-item.active {
    color: var(--gold);
    border-left-color: var(--gold);
    background: rgba(201,168,76,0.08);
  }
  .nav-item .icon { font-size: 1rem; width: 20px; text-align: center; }
  .sidebar-footer {
    margin-top: auto;
    padding: 20px 24px;
    border-top: 1px solid var(--border);
  }

  /* ---- MAIN CONTENT ---- */
  .main {
    margin-left: 260px;
    flex: 1;
    padding: 32px 40px;
    min-height: 100vh;
  }
  .page { display: none; }
  .page.active { display: block; }

  /* ---- PAGE HEADER ---- */
  .page-header {
    margin-bottom: 32px;
    padding-bottom: 20px;
    border-bottom: 1px solid var(--border);
  }
  .page-header h1 {
    font-family: 'Playfair Display', serif;
    color: var(--gold);
    font-size: 1.8rem;
    margin-bottom: 4px;
  }
  .page-header p {
    color: var(--text2);
    font-style: italic;
    font-size: 0.85rem;
  }

  /* ---- CARDS ---- */
  .card {
    background: var(--bg2);
    border: 1px solid var(--border);
    padding: 24px;
    margin-bottom: 20px;
  }
  .card-title {
    font-family: 'Playfair Display', serif;
    color: var(--gold);
    font-size: 1.1rem;
    margin-bottom: 16px;
    padding-bottom: 10px;
    border-bottom: 1px solid var(--border);
  }

  /* ---- STATS GRID ---- */
  .stats-grid {
    display: grid;
    grid-template-columns: repeat(4, 1fr);
    gap: 16px;
    margin-bottom: 28px;
  }
  .stat-card {
    background: var(--bg2);
    border: 1px solid var(--border);
    border-top: 2px solid var(--gold);
    padding: 20px;
    text-align: center;
  }
  .stat-number {
    font-family: 'Playfair Display', serif;
    font-size: 2rem;
    color: var(--gold);
    display: block;
  }
  .stat-label {
    font-size: 0.75rem;
    color: var(--text2);
    text-transform: uppercase;
    letter-spacing: 0.1em;
    margin-top: 4px;
  }

  /* ---- TABLE ---- */
  .table-wrap { overflow-x: auto; }
  table {
    width: 100%;
    border-collapse: collapse;
    font-size: 0.85rem;
  }
  thead tr { border-bottom: 2px solid var(--gold); }
  thead th {
    text-align: left;
    padding: 10px 14px;
    color: var(--gold);
    font-family: 'Playfair Display', serif;
    font-weight: 400;
    letter-spacing: 0.05em;
    font-size: 0.8rem;
  }
  tbody tr {
    border-bottom: 1px solid var(--border);
    transition: background 0.1s;
  }
  tbody tr:hover { background: rgba(201,168,76,0.04); }
  tbody td { padding: 10px 14px; color: var(--text); }

  /* ---- SEARCH ---- */
  .search-bar {
    display: flex;
    gap: 10px;
    margin-bottom: 20px;
  }
  .search-bar input {
    flex: 1;
    background: var(--bg3);
    border: 1px solid var(--border);
    color: var(--cream);
    padding: 10px 16px;
    font-family: 'Lora', serif;
    font-size: 0.9rem;
    outline: none;
  }
  .search-bar input:focus { border-color: var(--gold); }
  .search-bar select {
    background: var(--bg3);
    border: 1px solid var(--border);
    color: var(--cream);
    padding: 10px 12px;
    font-family: 'Lora', serif;
    outline: none;
  }

  /* ---- BADGE ---- */
  .badge {
    display: inline-block;
    padding: 2px 8px;
    font-size: 0.7rem;
    letter-spacing: 0.05em;
    text-transform: uppercase;
  }
  .badge-gold { background: rgba(201,168,76,0.15); color: var(--gold); border: 1px solid var(--gold); }
  .badge-green { background: rgba(42,92,58,0.3); color: #7bc99a; border: 1px solid #2a5c3a; }
  .badge-red { background: rgba(139,32,32,0.3); color: #e07070; border: 1px solid var(--red); }
  .badge-gray { background: rgba(100,90,70,0.3); color: var(--text2); border: 1px solid var(--border); }

  /* ---- ALERT ---- */
  .alert {
    padding: 12px 16px;
    margin-bottom: 16px;
    font-size: 0.85rem;
    border-left: 3px solid;
  }
  .alert-error { border-color: var(--red); background: rgba(139,32,32,0.1); color: #e07070; }
  .alert-success { border-color: var(--green2); background: rgba(42,92,58,0.1); color: #7bc99a; }
  .alert-info { border-color: var(--gold); background: rgba(201,168,76,0.08); color: var(--gold); }

  /* ---- MODAL ---- */
  .modal-overlay {
    display: none;
    position: fixed;
    inset: 0;
    background: rgba(0,0,0,0.7);
    z-index: 1000;
    align-items: center;
    justify-content: center;
  }
  .modal-overlay.open { display: flex; }
  .modal {
    background: var(--bg2);
    border: 1px solid var(--border);
    border-top: 2px solid var(--gold);
    padding: 32px;
    width: 520px;
    max-height: 80vh;
    overflow-y: auto;
    box-shadow: var(--shadow);
  }
  .modal h2 {
    font-family: 'Playfair Display', serif;
    color: var(--gold);
    margin-bottom: 20px;
  }
  .modal-actions {
    display: flex;
    gap: 10px;
    justify-content: flex-end;
    margin-top: 20px;
    padding-top: 16px;
    border-top: 1px solid var(--border);
  }

  /* ---- RATING ---- */
  .stars { color: var(--gold); font-size: 1.2rem; cursor: pointer; }
  .stars span { opacity: 0.3; transition: opacity 0.1s; }
  .stars span.on { opacity: 1; }

  /* ---- WISHLIST ---- */
  .wishlist-item {
    display: flex;
    align-items: center;
    justify-content: space-between;
    padding: 10px 0;
    border-bottom: 1px solid var(--border);
  }

  /* ---- ANUNTURI ---- */
  .anunt {
    background: var(--bg3);
    border: 1px solid var(--border);
    border-left: 3px solid var(--gold);
    padding: 16px 20px;
    margin-bottom: 12px;
  }
  .anunt-data { font-size: 0.75rem; color: var(--text2); margin-bottom: 4px; }
  .anunt-titlu {
    font-family: 'Playfair Display', serif;
    color: var(--cream);
    margin-bottom: 6px;
  }
  .anunt-text { font-size: 0.85rem; color: var(--text2); }

  /* ---- CHATBOT ---- */
  #chatbot-btn {
    position: fixed;
    bottom: 28px; right: 28px;
    width: 52px; height: 52px;
    background: var(--gold);
    color: var(--bg);
    border: none;
    border-radius: 50%;
    font-size: 1.4rem;
    cursor: pointer;
    box-shadow: var(--shadow);
    z-index: 500;
    display: none;
  }
  #chatbot-box {
    position: fixed;
    bottom: 92px; right: 28px;
    width: 340px;
    background: var(--bg2);
    border: 1px solid var(--border);
    border-top: 2px solid var(--gold);
    box-shadow: var(--shadow);
    z-index: 500;
    display: none;
    flex-direction: column;
  }
  #chatbot-box.open { display: flex; }
  .chat-header {
    padding: 12px 16px;
    border-bottom: 1px solid var(--border);
    font-family: 'Playfair Display', serif;
    color: var(--gold);
    font-size: 0.9rem;
  }
  .chat-messages {
    flex: 1;
    height: 280px;
    overflow-y: auto;
    padding: 12px;
    display: flex;
    flex-direction: column;
    gap: 8px;
  }
  .msg {
    padding: 8px 12px;
    font-size: 0.82rem;
    max-width: 85%;
    line-height: 1.5;
  }
  .msg-bot {
    background: var(--bg3);
    border: 1px solid var(--border);
    color: var(--text);
    align-self: flex-start;
  }
  .msg-user {
    background: rgba(201,168,76,0.12);
    border: 1px solid var(--border);
    color: var(--cream);
    align-self: flex-end;
  }
  .chat-input {
    display: flex;
    border-top: 1px solid var(--border);
  }
  .chat-input input {
    flex: 1;
    background: var(--bg3);
    border: none;
    color: var(--cream);
    padding: 10px 12px;
    font-family: 'Lora', serif;
    font-size: 0.82rem;
    outline: none;
  }
  .chat-input button {
    background: var(--gold);
    color: var(--bg);
    border: none;
    padding: 0 16px;
    cursor: pointer;
    font-size: 0.9rem;
  }

  /* ---- DIVIDER ---- */
  .divider {
    border: none;
    border-top: 1px solid var(--border);
    margin: 20px 0;
  }

  /* ---- GRID ---- */
  .grid-2 { display: grid; grid-template-columns: 1fr 1fr; gap: 16px; }
  .grid-3 { display: grid; grid-template-columns: 1fr 1fr 1fr; gap: 16px; }

  /* ---- SCROLLBAR ---- */
  ::-webkit-scrollbar { width: 6px; height: 6px; }
  ::-webkit-scrollbar-track { background: var(--bg); }
  ::-webkit-scrollbar-thumb { background: var(--border); }
  ::-webkit-scrollbar-thumb:hover { background: var(--gold); }

  /* ---- RESPONSIVE ---- */
  @media (max-width: 900px) {
    .stats-grid { grid-template-columns: repeat(2, 1fr); }
    .main { padding: 20px; }
  }
</style>
</head>
<body>

<!-- ================================================================ -->
<!-- LOGIN PAGE -->
<!-- ================================================================ -->
<div id="login-page">
  <div class="login-box">
    <h1>Biblioteca Universitară</h1>
    <p class="subtitle">Universitatea Ștefan cel Mare · Suceava</p>
    <div class="ornament">✦ ✦ ✦</div>
    <div id="login-error" class="alert alert-error" style="display:none"></div>
    <div class="form-group">
      <label>ID Utilizator</label>
      <input type="text" id="login-id" placeholder="ex: STAFF-001, STU-1001" autocomplete="off">
    </div>
    <div class="form-group">
      <label>Parolă</label>
      <input type="password" id="login-parola" placeholder="••••••••">
    </div>
    <button class="btn btn-gold btn-full" onclick="doLogin()">Autentificare</button>
  </div>
</div>

<!-- ================================================================ -->
<!-- APP -->
<!-- ================================================================ -->
<div id="app">
  <div class="layout">

    <!-- SIDEBAR -->
    <nav class="sidebar">
      <div class="sidebar-header">
        <h2>Biblioteca<br>Universitară Suceava</h2>
        <div class="user-info" id="user-info-sidebar">
          <div id="user-name-sidebar">—</div>
          <span class="user-role" id="user-role-sidebar">—</span>
        </div>
      </div>

      <div id="nav-staff" style="display:none">
        <div class="nav-section">
          <div class="nav-section-title">Gestiune</div>
          <div class="nav-item" onclick="showPage('dashboard')"><span class="icon">⊞</span> Dashboard</div>
          <div class="nav-item" id="nav-carti" onclick="showPage('carti')"><span class="icon">📚</span> Cărți</div>
          <div class="nav-item" id="nav-utilizatori" onclick="showPage('utilizatori')"><span class="icon">👥</span> Utilizatori</div>
          <div class="nav-item" id="nav-imprumuturi" onclick="showPage('imprumuturi')"><span class="icon">📋</span> Împrumuturi</div>
        </div>
        <div class="nav-section">
          <div class="nav-section-title">Instrumente</div>
          <div class="nav-item" onclick="showPage('procese')"><span class="icon">📄</span> Procese Verbale</div>
          <div class="nav-item" onclick="showPage('cautare')"><span class="icon">🔍</span> Căutare</div>
          <div class="nav-item" onclick="showPage('statistici')"><span class="icon">📊</span> Statistici</div>
          <div class="nav-item" onclick="showPage('anunturi')"><span class="icon">📢</span> Anunțuri</div>
          <div class="nav-item" onclick="showPage('despre')"><span class="icon">🏛</span> Despre</div>
        </div>
      </div>

      <div id="nav-user" style="display:none">
        <div class="nav-section">
          <div class="nav-item" onclick="showPage('dashboard')"><span class="icon">⊞</span> Acasă</div>
          <div class="nav-item" onclick="showPage('cautare')"><span class="icon">🔍</span> Caută Cărți</div>
          <div class="nav-item" onclick="showPage('profil')"><span class="icon">👤</span> Profilul Meu</div>
          <div class="nav-item" onclick="showPage('istoric')"><span class="icon">📖</span> Istoricul Meu</div>
          <div class="nav-item" onclick="showPage('wishlist')"><span class="icon">🔖</span> Lista de Lectură</div>
          <div class="nav-item" onclick="showPage('recomandari')"><span class="icon">✨</span> Recomandări</div>
          <div class="nav-item" onclick="showPage('anunturi')"><span class="icon">📢</span> Anunțuri</div>
          <div class="nav-item" onclick="showPage('despre')"><span class="icon">🏛</span> Despre</div>
        </div>
      </div>

      <div class="sidebar-footer">
        <button class="btn btn-outline btn-full" onclick="doLogout()">Deconectare</button>
      </div>
    </nav>

    <!-- MAIN -->
    <main class="main">

      <!-- DASHBOARD -->
      <div class="page" id="page-dashboard">
        <div class="page-header">
          <h1 id="dash-title">Bun venit</h1>
          <p id="dash-subtitle">Biblioteca Universitară Suceava</p>
        </div>
        <div class="stats-grid" id="stats-grid"></div>
        <div class="grid-2">
          <div class="card">
            <div class="card-title">Anunțuri Recente</div>
            <div id="dash-anunturi"></div>
          </div>
          <div class="card">
            <div class="card-title">Activitate Recentă</div>
            <div id="dash-activitate" style="color:var(--text2); font-style:italic; font-size:0.85rem;">
              Nicio activitate recentă.
            </div>
          </div>
        </div>
      </div>

      <!-- CARTI -->
      <div class="page" id="page-carti">
        <div class="page-header">
          <h1>Inventar Cărți</h1>
          <p>Gestionează colecția bibliotecii</p>
        </div>
        <div class="search-bar">
          <input type="text" id="carti-search" placeholder="Caută după titlu, autor, ISBN..." oninput="cautaCarti()">
          <select id="carti-tip" onchange="cautaCarti()">
            <option value="">Toate tipurile</option>
            <option value="Fictiune">Ficțiune</option>
            <option value="Tehnica">Tehnică</option>
            <option value="Educativa">Educativă</option>
            <option value="Copii">Copii</option>
            <option value="Referinta">Referință</option>
            <option value="Religioasa">Religioasă</option>
            <option value="Periodic">Periodic</option>
            <option value="ManuscrisRar">Manuscris Rar</option>
          </select>
          <button class="btn btn-gold" onclick="showModal('modal-adauga-carte')">+ Adaugă</button>
        </div>
        <div class="table-wrap">
          <table id="tabel-carti">
            <thead><tr>
              <th>Titlu</th><th>Autor</th><th>Tip</th>
              <th>An</th><th>Disponibile</th><th>Total</th>
            </tr></thead>
            <tbody id="tbody-carti"></tbody>
          </table>
        </div>
      </div>

      <!-- UTILIZATORI -->
      <div class="page" id="page-utilizatori">
        <div class="page-header">
          <h1>Utilizatori</h1>
          <p>Gestionează membrii bibliotecii</p>
        </div>
        <div class="search-bar">
          <input type="text" id="user-search" placeholder="Caută după ID, nume..." oninput="cautaUtilizatori()">
          <button class="btn btn-gold" onclick="showModal('modal-adauga-user')">+ Adaugă</button>
        </div>
        <div class="table-wrap">
          <table>
            <thead><tr>
              <th>ID</th><th>Nume</th><th>Tip</th>
              <th>Împrumuturi</th><th>Taxe</th><th>Acțiuni</th>
            </tr></thead>
            <tbody id="tbody-utilizatori"></tbody>
          </table>
        </div>
      </div>

      <!-- IMPRUMUTURI -->
      <div class="page" id="page-imprumuturi">
        <div class="page-header">
          <h1>Împrumuturi & Returnări</h1>
          <p>Gestionează circulația cărților</p>
        </div>
        <div class="grid-2" style="margin-bottom:24px">
          <div class="card">
            <div class="card-title">Înregistrează Împrumut</div>
            <div class="form-group">
              <label>ID Utilizator</label>
              <input type="text" id="imp-user-id" placeholder="ex: STU-1001">
            </div>
            <div class="form-group">
              <label>ISBN Carte</label>
              <input type="text" id="imp-isbn" placeholder="ex: ISBN-F001">
            </div>
            <div class="form-group">
              <label>Data (zi/luna/an)</label>
              <div style="display:flex;gap:8px">
                <input type="number" id="imp-zi" placeholder="zi" min="1" max="31" style="width:33%">
                <input type="number" id="imp-luna" placeholder="luna" min="1" max="12" style="width:33%">
                <input type="number" id="imp-an" placeholder="an" value="2024" style="width:34%">
              </div>
            </div>
            <div id="imp-msg"></div>
            <button class="btn btn-gold" onclick="doImprumut()">Înregistrează</button>
          </div>
          <div class="card">
            <div class="card-title">Returnare Carte</div>
            <div class="form-group">
              <label>ID Utilizator</label>
              <input type="text" id="ret-user-id" placeholder="ex: STU-1001">
            </div>
            <div class="form-group">
              <label>Cod Exemplar</label>
              <input type="text" id="ret-cod" placeholder="ex: BIB-2024-00001">
            </div>
            <div class="form-group">
              <label>Zile întârziere</label>
              <input type="number" id="ret-zile" value="0" min="0">
            </div>
            <div class="form-group">
              <label>Rating carte (1-5 stele)</label>
              <div class="stars" id="rating-stars">
                <span onclick="setRating(1)">★</span>
                <span onclick="setRating(2)">★</span>
                <span onclick="setRating(3)">★</span>
                <span onclick="setRating(4)">★</span>
                <span onclick="setRating(5)">★</span>
              </div>
              <input type="hidden" id="ret-rating" value="0">
            </div>
            <div id="ret-msg"></div>
            <button class="btn btn-gold" onclick="doReturnare()">Returnează</button>
          </div>
        </div>
        <div class="card">
          <div class="card-title">Încasare Taxă</div>
          <div style="display:flex;gap:12px;align-items:flex-end">
            <div class="form-group" style="flex:1;margin:0">
              <label>ID Utilizator</label>
              <input type="text" id="taxa-user-id" placeholder="ex: STU-1001">
            </div>
            <div class="form-group" style="flex:1;margin:0">
              <label>Suma (RON)</label>
              <input type="number" id="taxa-suma" placeholder="0.00" step="0.01">
            </div>
            <button class="btn btn-gold" onclick="doIncasare()">Încasează</button>
          </div>
          <div id="taxa-msg" style="margin-top:10px"></div>
        </div>
      </div>

      <!-- PROCESE VERBALE -->
      <div class="page" id="page-procese">
        <div class="page-header">
          <h1>Procese Verbale</h1>
          <p>Deteriorări și nerestituiri</p>
        </div>
        <div class="grid-2">
          <div class="card">
            <div class="card-title">Proces Verbal Deteriorare</div>
            <div class="form-group">
              <label>ID Utilizator</label>
              <input type="text" id="pv-det-user" placeholder="ex: STU-1001" oninput="preiaDateUser('pv-det-user','pv-det-info')">
            </div>
            <div id="pv-det-info" class="alert alert-info" style="display:none"></div>
            <div class="form-group">
              <label>Cod Exemplar</label>
              <input type="text" id="pv-det-cod" placeholder="ex: BIB-2024-00001">
            </div>
            <div class="form-group">
              <label>Descriere deteriorare</label>
              <textarea id="pv-det-desc" rows="3" style="width:100%;background:var(--bg3);border:1px solid var(--border);color:var(--cream);padding:10px;font-family:Lora,serif;resize:vertical"></textarea>
            </div>
            <div class="form-group">
              <label>Valoare daune estimate (RON)</label>
              <input type="number" id="pv-det-val" step="0.01" placeholder="0.00">
            </div>
            <div id="pv-det-msg"></div>
            <button class="btn btn-gold" onclick="genereazaPVDeteriorate()">Generează PV</button>
          </div>
          <div class="card">
            <div class="card-title">Proces Verbal Neretur</div>
            <div class="form-group">
              <label>ID Utilizator</label>
              <input type="text" id="pv-ner-user" placeholder="ex: STU-1001" oninput="preiaDateUser('pv-ner-user','pv-ner-info')">
            </div>
            <div id="pv-ner-info" class="alert alert-info" style="display:none"></div>
            <div class="form-group">
              <label>ISBN Carte</label>
              <input type="text" id="pv-ner-isbn" placeholder="ex: ISBN-F001">
            </div>
            <div class="form-group">
              <label>Zile depășite</label>
              <input type="number" id="pv-ner-zile" placeholder="0" min="0">
            </div>
            <div id="pv-ner-msg"></div>
            <button class="btn btn-gold" onclick="genereazaPVNeretur()">Generează PV</button>
          </div>
        </div>
        <div class="card" id="pv-preview" style="display:none">
          <div class="card-title">Previzualizare Proces Verbal</div>
          <div id="pv-content" style="font-family:'EB Garamond',serif;font-size:0.95rem;line-height:1.8;color:var(--cream)"></div>
          <div style="margin-top:16px">
            <button class="btn btn-gold" onclick="descarcaPV()">📄 Descarcă PDF</button>
          </div>
        </div>
      </div>

      <!-- CAUTARE -->
      <div class="page" id="page-cautare">
        <div class="page-header">
          <h1>Căutare Avansată</h1>
          <p>Găsește orice carte din colecție</p>
        </div>
        <div class="card">
          <div style="display:flex;gap:12px;flex-wrap:wrap;align-items:flex-end">
            <div class="form-group" style="flex:2;margin:0">
              <label>Caută</label>
              <input type="text" id="caut-text" placeholder="Titlu, autor, ISBN...">
            </div>
            <div class="form-group" style="flex:1;margin:0">
              <label>Câmp</label>
              <select id="caut-camp">
                <option value="titlu">Titlu</option>
                <option value="autor">Autor</option>
                <option value="isbn">ISBN</option>
                <option value="an">An apariție</option>
              </select>
            </div>
            <button class="btn btn-gold" onclick="executaCautare()">Caută</button>
          </div>
        </div>
        <div id="caut-rezultate"></div>
      </div>

      <!-- STATISTICI -->
      <div class="page" id="page-statistici">
        <div class="page-header">
          <h1>Statistici & Rapoarte</h1>
          <p>Situația curentă a bibliotecii</p>
        </div>
        <div class="stats-grid" id="stats-full"></div>
        <div class="grid-2">
          <div class="card">
            <div class="card-title">Distribuție pe Tipuri</div>
            <div id="stats-tipuri"></div>
          </div>
          <div class="card">
            <div class="card-title">Împrumuturi Active</div>
            <div id="stats-imp"></div>
          </div>
        </div>
      </div>

      <!-- PROFIL -->
      <div class="page" id="page-profil">
        <div class="page-header">
          <h1>Profilul Meu</h1>
          <p>Informațiile contului tău</p>
        </div>
        <div class="grid-2">
          <div class="card">
            <div class="card-title">Informații</div>
            <div id="profil-info"></div>
          </div>
          <div class="card">
            <div class="card-title">Schimbă Parola</div>
            <div class="form-group">
              <label>Parola Veche</label>
              <input type="password" id="parola-veche">
            </div>
            <div class="form-group">
              <label>Parola Nouă</label>
              <input type="password" id="parola-noua">
            </div>
            <div class="form-group">
              <label>Confirmă Parola</label>
              <input type="password" id="parola-confirm">
            </div>
            <div id="parola-msg"></div>
            <button class="btn btn-gold" onclick="schimbaParola()">Actualizează</button>
          </div>
        </div>
      </div>

      <!-- ISTORIC -->
      <div class="page" id="page-istoric">
        <div class="page-header">
          <h1>Istoricul Meu</h1>
          <p>Cărțile pe care le-ai citit</p>
        </div>
        <div class="card">
          <div class="card-title">Cărți Citite</div>
          <div id="istoric-content">
            <p style="color:var(--text2);font-style:italic">Nicio carte înregistrată încă.</p>
          </div>
        </div>
      </div>

      <!-- WISHLIST -->
      <div class="page" id="page-wishlist">
        <div class="page-header">
          <h1>Lista de Lectură</h1>
          <p>Cărțile pe care vrei să le citești</p>
        </div>
        <div class="card">
          <div class="card-title">Adaugă la Listă</div>
          <div style="display:flex;gap:10px">
            <input type="text" id="wish-isbn" placeholder="ISBN carte" style="flex:1;background:var(--bg3);border:1px solid var(--border);color:var(--cream);padding:10px;font-family:Lora,serif;outline:none">
            <button class="btn btn-gold" onclick="adaugaWishlist()">Adaugă</button>
          </div>
        </div>
        <div class="card">
          <div class="card-title">Lista Ta</div>
          <div id="wishlist-content">
            <p style="color:var(--text2);font-style:italic">Lista ta de lectură este goală.</p>
          </div>
        </div>
      </div>

      <!-- RECOMANDARI -->
      <div class="page" id="page-recomandari">
        <div class="page-header">
          <h1>Recomandări</h1>
          <p>Descoperă cărți care ți s-ar potrivi</p>
        </div>
        <div class="card">
          <div class="card-title">Caută după Gen</div>
          <div style="display:flex;gap:8px;flex-wrap:wrap">
            <button class="btn btn-outline" onclick="getRecomandari('SF')">🚀 SF</button>
            <button class="btn btn-outline" onclick="getRecomandari('Fantasy')">🧙 Fantasy</button>
            <button class="btn btn-outline" onclick="getRecomandari('Horror')">👻 Horror</button>
            <button class="btn btn-outline" onclick="getRecomandari('Thriller')">🔪 Thriller</button>
            <button class="btn btn-outline" onclick="getRecomandari('Mister')">🔍 Mister</button>
            <button class="btn btn-outline" onclick="getRecomandari('Roman')">📖 Roman</button>
            <button class="btn btn-outline" onclick="getRecomandari('Aventuri')">⚔️ Aventuri</button>
            <button class="btn btn-outline" onclick="getRecomandari('Distopie')">🌍 Distopie</button>
            <button class="btn btn-outline" onclick="getRecomandari('Cyberpunk')">🤖 Cyberpunk</button>
            <button class="btn btn-outline" onclick="getRecomandari('Clasici')">🏛️ Clasici</button>
            <button class="btn btn-outline" onclick="getRecomandari('Poezie')">✍️ Poezie</button>
            <button class="btn btn-outline" onclick="getRecomandari('C++')">💻 C++</button>
            <button class="btn btn-outline" onclick="getRecomandari('Python')">🐍 Python</button>
            <button class="btn btn-outline" onclick="getRecomandari('Java')">☕ Java</button>
            <button class="btn btn-outline" onclick="getRecomandari('Machine Learning')">🧠 AI/ML</button>
            <button class="btn btn-outline" onclick="getRecomandari('Matematica')">📐 Matematica</button>
            <button class="btn btn-outline" onclick="getRecomandari('Medicina')">🏥 Medicina</button>
            <button class="btn btn-outline" onclick="getRecomandari('Drept')">⚖️ Drept</button>
            <button class="btn btn-outline" onclick="getRecomandari('Copii')">🎨 Copii</button>
            <button class="btn btn-outline" onclick="getRecomandari('Dictionar')">📚 Dictionare</button>
          </div>
          <div style="margin-top:12px">
            <div style="display:flex;gap:10px">
              <input type="text" id="rec-custom" placeholder="Caută alt gen..." 
                style="flex:1;background:var(--bg3);border:1px solid var(--border);color:var(--cream);padding:10px;font-family:Lora,serif;outline:none">
              <button class="btn btn-gold" onclick="getRecomandari(document.getElementById('rec-custom').value)">Caută</button>
            </div>
          </div>
        </div>
        <div id="rec-rezultate"></div>
      </div>

      <!-- ANUNTURI -->
      <div class="page" id="page-anunturi">
        <div class="page-header">
          <h1>Anunțuri & Evenimente</h1>
          <p>Noutăți de la Biblioteca Universitară</p>
        </div>
        <div id="anunturi-list"></div>
        <div class="card" id="card-adauga-anunt" style="display:none">
          <div class="card-title">Adaugă Anunț Nou</div>
          <div class="form-group">
            <label>Titlu</label>
            <input type="text" id="anunt-titlu-input">
          </div>
          <div class="form-group">
            <label>Text</label>
            <textarea id="anunt-text-input" rows="4" style="width:100%;background:var(--bg3);border:1px solid var(--border);color:var(--cream);padding:10px;font-family:Lora,serif;resize:vertical"></textarea>
          </div>
          <div class="form-group">
            <label>Data eveniment</label>
            <input type="text" id="anunt-data-input" placeholder="ex: 15 Iunie 2025">
          </div>
          <button class="btn btn-gold" onclick="adaugaAnunt()">Publică</button>
        </div>
      </div>

      <!-- DESPRE -->
      <div class="page" id="page-despre">
        <div class="page-header">
          <h1>Despre Bibliotecă</h1>
          <p>Misiune, valori și parteneriate</p>
        </div>
        <div class="grid-2">
          <div class="card">
            <div class="card-title">Despre Noi</div>
            <p style="color:var(--text);line-height:1.8;font-size:0.9rem">
              Biblioteca Universitară a Universității <em>Ștefan cel Mare</em> din Suceava
              oferă acces la o colecție vastă de resurse academice, literare și științifice.
              Fondată în 1990, biblioteca deservește studenți, cadre didactice și cercetători
              din toate domeniile de studiu ale universității.
            </p>
            <hr class="divider">
            <p style="color:var(--text2);font-size:0.85rem;line-height:1.7">
              📍 Str. Universității nr. 13, Suceava<br>
              📞 0230 216 147<br>
              ✉️ biblioteca@usm.ro<br>
              🌐 www.biblioteca.usv.ro
            </p>
          </div>
          <div class="card">
            <div class="card-title">Program</div>
            <table style="width:100%;font-size:0.85rem">
              <tbody>
                <tr><td style="color:var(--text2);padding:6px 0">Luni — Vineri</td><td style="color:var(--cream)">08:00 — 20:00</td></tr>
                <tr><td style="color:var(--text2);padding:6px 0">Sâmbătă</td><td style="color:var(--cream)">09:00 — 14:00</td></tr>
                <tr><td style="color:var(--text2);padding:6px 0">Duminică</td><td style="color:var(--cream)">Închis</td></tr>
              </tbody>
            </table>
            <hr class="divider">
            <div class="card-title" style="margin-bottom:12px">Sponsori & Parteneri</div>
            <div style="color:var(--text2);font-size:0.85rem;line-height:1.9">
              🏛 Ministerul Educației Naționale<br>
              📖 Biblioteca Națională a României<br>
              🇪🇺 Programul Erasmus+<br>
              🏢 Consiliul Județean Suceava<br>
              📚 Fundația Culturală Română
            </div>
          </div>
        </div>
      </div>

    </main>
  </div>
</div>

<!-- CHATBOT -->
<button id="chatbot-btn" onclick="toggleChat()">💬</button>
<div id="chatbot-box">
  <div class="chat-header">✦ Asistent Bibliotecă</div>
  <div class="chat-messages" id="chat-messages">
    <div class="msg msg-bot">Bună ziua! Sunt asistentul bibliotecii. Cu ce vă pot ajuta?</div>
  </div>
  <div class="chat-input">
    <input type="text" id="chat-input" placeholder="Scrieți o întrebare..." onkeydown="if(event.key==='Enter')sendChat()">
    <button onclick="sendChat()">➤</button>
  </div>
</div>

<!-- MODALS -->
<div class="modal-overlay" id="modal-adauga-carte">
  <div class="modal">
    <h2>Adaugă Carte Nouă</h2>
    <div class="form-group"><label>ISBN</label><input type="text" id="m-isbn"></div>
    <div class="form-group"><label>Titlu</label><input type="text" id="m-titlu"></div>
    <div class="form-group"><label>Autor - Nume</label><input type="text" id="m-autor-nm"></div>
    <div class="form-group"><label>Autor - Prenume</label><input type="text" id="m-autor-pr"></div>
    <div class="form-group"><label>Editura</label><input type="text" id="m-editura"></div>
    <div class="form-group"><label>An apariție</label><input type="number" id="m-an" value="2024"></div>
    <div class="form-group">
      <label>Tip</label>
      <select id="m-tip">
        <option value="Fictiune">Ficțiune</option>
        <option value="Tehnica">Tehnică</option>
        <option value="Educativa">Educativă</option>
        <option value="Copii">Copii</option>
      </select>
    </div>
    <div class="form-group"><label>Gen / Domeniu</label><input type="text" id="m-gen" placeholder="ex: SF, C++, Matematica"></div>
    <div class="form-group"><label>Nr. Pagini</label><input type="number" id="m-pagini" value="0"></div>
    <div class="form-group"><label>Preț Catalog (RON)</label><input type="number" id="m-pret" step="0.01" value="0"></div>
    <div id="m-carte-msg"></div>
    <div class="modal-actions">
      <button class="btn btn-outline" onclick="closeModal('modal-adauga-carte')">Anulează</button>
      <button class="btn btn-gold" onclick="adaugaCarte()">Adaugă</button>
    </div>
  </div>
</div>

<div class="modal-overlay" id="modal-adauga-user">
  <div class="modal">
    <h2>Adaugă Utilizator</h2>
    <div class="form-group"><label>ID</label><input type="text" id="u-id" placeholder="ex: STU-100, BAS-200"></div>
    <div class="form-group"><label>Nume</label><input type="text" id="u-nm"></div>
    <div class="form-group"><label>Prenume</label><input type="text" id="u-pr"></div>
    <div class="form-group"><label>Contact (email)</label><input type="text" id="u-cont"></div>
    <div class="form-group"><label>Parolă</label><input type="password" id="u-parola"></div>
    <div class="form-group">
      <label>Tip</label>
      <select id="u-tip" onchange="updateUserForm()">
        <option value="Basic">Basic</option>
        <option value="Student">Student</option>
      </select>
    </div>
    <div id="u-extra-student" style="display:none">
      <div class="form-group"><label>Facultate</label><input type="text" id="u-fac"></div>
      <div class="form-group"><label>An Studiu</label><input type="number" id="u-an-st" value="1" min="1" max="6"></div>
      <div class="form-group"><label>Nr. Matricol</label><input type="text" id="u-matr"></div>
    </div>
    <div id="u-msg"></div>
    <div class="modal-actions">
      <button class="btn btn-outline" onclick="closeModal('modal-adauga-user')">Anulează</button>
      <button class="btn btn-gold" onclick="adaugaUser()">Adaugă</button>
    </div>
  </div>
</div>

<!-- ================================================================ -->
<!-- JAVASCRIPT -->
<!-- ================================================================ -->
<script>
let token = '';
let userInfo = null;
let wishlist = JSON.parse(localStorage.getItem('wishlist_' + '') || '[]');
let currentRating = 0;
let currentPV = '';

const API = '';

async function api(method, path, body) {
  const opts = {
    method,
    headers: {'Content-Type':'application/json', 'Authorization':'Bearer '+token}
  };
  if (body) opts.body = JSON.stringify(body);
  const r = await fetch(API + path, opts);
  return r.json().catch(() => ({}));
}

// ---- LOGIN ----
async function doLogin() {
  const id = document.getElementById('login-id').value.trim();
  const pw = document.getElementById('login-parola').value;
  const err = document.getElementById('login-error');
  err.style.display = 'none';
  if (!id || !pw) { showErr(err, 'Completați toate câmpurile.'); return; }
  const r = await fetch('/api/login', {
    method:'POST',
    headers:{'Content-Type':'application/json'},
    body: JSON.stringify({id, parola: pw})
  });
  const d = await r.json();
  if (d.ok) {
    token = d.token;
    userInfo = d.user;
    wishlist = JSON.parse(localStorage.getItem('wishlist_'+userInfo.id) || '[]');
    initApp();
  } else {
    showErr(err, d.mesaj || 'Autentificare eșuată.');
  }
}

document.getElementById('login-parola').addEventListener('keydown', e => {
  if (e.key === 'Enter') doLogin();
});

function showErr(el, msg) { el.textContent = msg; el.style.display = 'block'; }

// ---- INIT APP ----
function initApp() {
  document.getElementById('login-page').style.display = 'none';
  document.getElementById('app').style.display = 'block';
  document.getElementById('chatbot-btn').style.display = 'flex';
  document.getElementById('chatbot-btn').style.alignItems = 'center';
  document.getElementById('chatbot-btn').style.justifyContent = 'center';

  document.getElementById('user-name-sidebar').textContent = userInfo.numeComplet;
  document.getElementById('user-role-sidebar').textContent = userInfo.tip;

  const isStaff = userInfo.tip === 'STAFF';
  document.getElementById('nav-staff').style.display = isStaff ? 'block' : 'none';
  document.getElementById('nav-user').style.display = isStaff ? 'none' : 'block';

  loadDashboard();
  showPage('dashboard');
}

// ---- LOGOUT ----
function doLogout() {
  token = '';
  userInfo = null;
  document.getElementById('login-page').style.display = 'flex';
  document.getElementById('app').style.display = 'none';
  document.getElementById('chatbot-btn').style.display = 'none';
  document.getElementById('login-id').value = '';
  document.getElementById('login-parola').value = '';
  document.getElementById('login-error').style.display = 'none';
}

// ---- PAGE NAVIGATION ----
function showPage(name) {
  document.querySelectorAll('.page').forEach(p => p.classList.remove('active'));
  document.querySelectorAll('.nav-item').forEach(n => n.classList.remove('active'));
  const p = document.getElementById('page-' + name);
  if (p) p.classList.add('active');
  document.querySelectorAll('.nav-item').forEach(n => {
    if (n.getAttribute('onclick') && n.getAttribute('onclick').includes("'"+name+"'"))
      n.classList.add('active');
  });
  if (name === 'carti')      loadCarti();
  if (name === 'utilizatori') loadUtilizatori();
  if (name === 'statistici') loadStatistici();
  if (name === 'profil')     loadProfil();
  if (name === 'anunturi')   loadAnunturi();
  if (name === 'wishlist')   renderWishlist();
  if (name === 'istoric')    loadIstoric();
  if (name === 'recomandari') document.getElementById('rec-rezultate').innerHTML='';
}

// ---- DASHBOARD ----
async function loadDashboard() {
  const d = await api('GET', '/api/statistici');
  if (!d) return;
  const g = document.getElementById('stats-grid');
  g.innerHTML = `
    <div class="stat-card"><span class="stat-number">${d.carti||0}</span><div class="stat-label">Titluri</div></div>
    <div class="stat-card"><span class="stat-number">${d.utilizatori||0}</span><div class="stat-label">Utilizatori</div></div>
    <div class="stat-card"><span class="stat-number">${d.autori||0}</span><div class="stat-label">Autori</div></div>
    <div class="stat-card"><span class="stat-number">${d.imprumuturi_active||0}</span><div class="stat-label">Împrumutate</div></div>
  `;
  document.getElementById('dash-title').textContent = 'Bun venit, ' + (userInfo?.numeComplet || '');
  loadAnunturiDash();
}

async function loadAnunturiDash() {
  const d = await api('GET', '/api/anunturi');
  const el = document.getElementById('dash-anunturi');
  if (!d || !d.anunturi || d.anunturi.length === 0) {
    el.innerHTML = '<p style="color:var(--text2);font-style:italic;font-size:0.85rem">Niciun anunț.</p>';
    return;
  }
  el.innerHTML = d.anunturi.slice(0,3).map(a => `
    <div class="anunt">
      <div class="anunt-data">${a.data}</div>
      <div class="anunt-titlu">${a.titlu}</div>
      <div class="anunt-text">${a.text.substring(0,100)}...</div>
    </div>
  `).join('');
}

// ---- CARTI ----
let toateCartile = [];
async function loadCarti() {
  const d = await api('GET', '/api/carti');
  if (!d || !d.carti) return;
  toateCartile = d.carti;
  renderCarti(toateCartile);
}

function renderCarti(carti) {
  const tb = document.getElementById('tbody-carti');
  tb.innerHTML = carti.map(c => `
    <tr>
      <td><strong style="color:var(--cream)">${c.titlu}</strong>${c.serie ? '<br><small style="color:var(--text2)">'+c.serie+'</small>' : ''}</td>
      <td style="color:var(--text2)">${c.autori}</td>
      <td><span class="badge badge-gold">${c.tip}</span></td>
      <td>${c.an}</td>
      <td><span class="${c.disponibile > 0 ? 'badge badge-green' : 'badge badge-red'}">${c.disponibile}</span></td>
      <td>${c.total}</td>
    </tr>
  `).join('');
}

function cautaCarti() {
  const q = document.getElementById('carti-search').value.toLowerCase();
  const tip = document.getElementById('carti-tip').value;
  const filtrate = toateCartile.filter(c => {
    const matchQ = !q || c.titlu.toLowerCase().includes(q) ||
                   c.autori.toLowerCase().includes(q) ||
                   c.isbn.toLowerCase().includes(q);
    const matchTip = !tip || c.tip === tip;
    return matchQ && matchTip;
  });
  renderCarti(filtrate);
}

// ---- UTILIZATORI ----
let toateUser = [];
async function loadUtilizatori() {
  const d = await api('GET', '/api/utilizatori');
  if (!d || !d.utilizatori) return;
  toateUser = d.utilizatori;
  renderUtilizatori(toateUser);
}

function renderUtilizatori(users) {
  const tb = document.getElementById('tbody-utilizatori');
  tb.innerHTML = users.map(u => `
    <tr>
      <td style="color:var(--text2);font-size:0.8rem">${u.id}</td>
      <td><strong style="color:var(--cream)">${u.numeComplet}</strong></td>
      <td><span class="badge badge-gold">${u.tip}</span></td>
      <td>${u.nrImprumuturi}/${u.limita}</td>
      <td style="color:${u.taxe > 0 ? '#e07070' : 'var(--text2)'}">${u.taxe} RON</td>
      <td><button class="btn btn-outline" style="padding:4px 10px;font-size:0.75rem" onclick="veziUtilizator('${u.id}')">Detalii</button></td>
    </tr>
  `).join('');
}

function cautaUtilizatori() {
  const q = document.getElementById('user-search').value.toLowerCase();
  renderUtilizatori(toateUser.filter(u =>
    u.id.toLowerCase().includes(q) || u.numeComplet.toLowerCase().includes(q)
  ));
}

async function veziUtilizator(id) {
  const d = await api('GET', '/api/utilizator?id=' + id);
  if (!d) return;
  alert(JSON.stringify(d, null, 2));
}

// ---- IMPRUMUT ----
async function doImprumut() {
  const uid = document.getElementById('imp-user-id').value.trim();
  const isbn = document.getElementById('imp-isbn').value.trim();
  const zi = parseInt(document.getElementById('imp-zi').value) || 1;
  const luna = parseInt(document.getElementById('imp-luna').value) || 1;
  const an = parseInt(document.getElementById('imp-an').value) || 2024;
  const msg = document.getElementById('imp-msg');
  const d = await api('POST', '/api/imprumut', {id_user: uid, isbn, zi, luna, an});
  msg.innerHTML = `<div class="alert ${d.ok ? 'alert-success' : 'alert-error'}">${d.mesaj}</div>`;
}

// ---- RETURNARE ----
function setRating(n) {
  currentRating = n;
  document.getElementById('ret-rating').value = n;
  document.querySelectorAll('#rating-stars span').forEach((s, i) => {
    s.classList.toggle('on', i < n);
  });
}

async function doReturnare() {
  const uid = document.getElementById('ret-user-id').value.trim();
  const cod = document.getElementById('ret-cod').value.trim();
  const zile = parseInt(document.getElementById('ret-zile').value) || 0;
  const rating = currentRating;
  const msg = document.getElementById('ret-msg');
  const d = await api('POST', '/api/returnare', {id_user: uid, cod_exemplar: cod, zile_intarziere: zile, rating});
  msg.innerHTML = `<div class="alert ${d.ok ? 'alert-success' : 'alert-error'}">${d.mesaj}</div>`;
  if (d.ok) { currentRating = 0; setRating(0); }
}

async function doIncasare() {
  const uid = document.getElementById('taxa-user-id').value.trim();
  const suma = parseFloat(document.getElementById('taxa-suma').value) || 0;
  const msg = document.getElementById('taxa-msg');
  const d = await api('POST', '/api/incasare', {id_user: uid, suma});
  msg.innerHTML = `<div class="alert ${d.ok ? 'alert-success' : 'alert-error'}">${d.mesaj}</div>`;
}

// ---- PROCESE VERBALE ----
async function preiaDateUser(inputId, infoId) {
  const id = document.getElementById(inputId).value.trim();
  const info = document.getElementById(infoId);
  if (id.length < 3) { info.style.display = 'none'; return; }
  const d = await api('GET', '/api/utilizator?id=' + id);
  if (d && d.id) {
    info.style.display = 'block';
    info.textContent = `${d.numeComplet} | ${d.tip} | Taxe: ${d.taxe} RON`;
  } else {
    info.style.display = 'none';
  }
}

async function genereazaPVDeteriorate() {
  const uid = document.getElementById('pv-det-user').value.trim();
  const cod = document.getElementById('pv-det-cod').value.trim();
  const desc = document.getElementById('pv-det-desc').value.trim();
  const val = parseFloat(document.getElementById('pv-det-val').value) || 0;
  const msg = document.getElementById('pv-det-msg');
  const d = await api('GET', '/api/utilizator?id=' + uid);
  if (!d || !d.id) { msg.innerHTML = '<div class="alert alert-error">Utilizatorul nu a fost găsit.</div>'; return; }
  const data = new Date().toLocaleDateString('ro-RO');
  currentPV = `PROCES VERBAL DE CONSTATARE A DETERIORĂRII

Nr. ___ / ${data}

Biblioteca Universitară "Ștefan cel Mare", Suceava

UTILIZATOR:
- Nume: ${d.numeComplet}
- ID: ${d.id}
- Contact: ${d.contact || '—'}

CARTE DETERIORATĂ:
- Cod Exemplar: ${cod}
- Descriere deteriorare: ${desc}
- Valoare daune estimate: ${val} RON

Prezentul proces verbal a fost întocmit în două exemplare, câte unul pentru fiecare parte.

Bibliotecar: _______________________     Utilizator: _______________________`;
  document.getElementById('pv-content').style.whiteSpace = 'pre-wrap';
  document.getElementById('pv-content').textContent = currentPV;
  document.getElementById('pv-preview').style.display = 'block';
  msg.innerHTML = '<div class="alert alert-success">Proces verbal generat.</div>';
}

async function genereazaPVNeretur() {
  const uid = document.getElementById('pv-ner-user').value.trim();
  const isbn = document.getElementById('pv-ner-isbn').value.trim();
  const zile = parseInt(document.getElementById('pv-ner-zile').value) || 0;
  const msg = document.getElementById('pv-ner-msg');
  const d = await api('GET', '/api/utilizator?id=' + uid);
  if (!d || !d.id) { msg.innerHTML = '<div class="alert alert-error">Utilizatorul nu a fost găsit.</div>'; return; }
  const data = new Date().toLocaleDateString('ro-RO');
  currentPV = `PROCES VERBAL DE NERESTITUIRE

Nr. ___ / ${data}

Biblioteca Universitară "Ștefan cel Mare", Suceava

UTILIZATOR:
- Nume: ${d.numeComplet}
- ID: ${d.id}
- Contact: ${d.contact || '—'}

CARTE NERESTITUITĂ:
- ISBN: ${isbn}
- Zile de întârziere: ${zile}
- Taxă acumulată: ${(zile * 1.5).toFixed(2)} RON

Utilizatorul are obligația să restituie cartea sau să plătească contravaloarea acesteia.

Bibliotecar: _______________________     Utilizator: _______________________`;
  document.getElementById('pv-content').style.whiteSpace = 'pre-wrap';
  document.getElementById('pv-content').textContent = currentPV;
  document.getElementById('pv-preview').style.display = 'block';
  msg.innerHTML = '<div class="alert alert-success">Proces verbal generat.</div>';
}

function descarcaPV() {
  const win = window.open('', '_blank');
  win.document.write(`<html><head><title>Proces Verbal</title>
    <style>body{font-family:Georgia,serif;padding:40px;font-size:14pt;line-height:1.8}
    pre{white-space:pre-wrap;font-family:Georgia,serif}</style></head>
    <body><pre>${currentPV}</pre>
    <script>window.print();window.close();<\/script></body></html>`);
  win.document.close();
}

// ---- CAUTARE ----
async function executaCautare() {
  const q = document.getElementById('caut-text').value.trim();
  const camp = document.getElementById('caut-camp').value;
  if (!q) return;
  let endpoint = '';
  if (camp === 'titlu') endpoint = '/api/cauta?tip=titlu&q=' + encodeURIComponent(q);
  else if (camp === 'autor') endpoint = '/api/cauta?tip=autor&q=' + encodeURIComponent(q);
  else if (camp === 'isbn') endpoint = '/api/carti';
  else if (camp === 'an') endpoint = '/api/cauta?tip=an&q=' + encodeURIComponent(q);
  const d = await api('GET', endpoint);
  const rez = document.getElementById('caut-rezultate');
  let carti = d.carti || d.rezultate || [];
  if (camp === 'isbn') carti = carti.filter(c => c.isbn.toLowerCase().includes(q.toLowerCase()));
  if (carti.length === 0) {
    rez.innerHTML = '<div class="alert alert-info">Niciun rezultat găsit.</div>';
    return;
  }
  rez.innerHTML = `<div class="card"><div class="card-title">${carti.length} rezultate</div>
    <div class="table-wrap"><table>
      <thead><tr><th>Titlu</th><th>Autor</th><th>Tip</th><th>An</th><th>Disponibile</th></tr></thead>
      <tbody>${carti.map(c=>`<tr>
        <td><strong style="color:var(--cream)">${c.titlu}</strong></td>
        <td style="color:var(--text2)">${c.autori}</td>
        <td><span class="badge badge-gold">${c.tip}</span></td>
        <td>${c.an}</td>
        <td><span class="${c.disponibile>0?'badge badge-green':'badge badge-red'}">${c.disponibile}</span></td>
      </tr>`).join('')}</tbody>
    </table></div></div>`;
}

// ---- STATISTICI ----
async function loadStatistici() {
  const d = await api('GET', '/api/statistici');
  if (!d) return;
  document.getElementById('stats-full').innerHTML = `
    <div class="stat-card"><span class="stat-number">${d.carti}</span><div class="stat-label">Titluri</div></div>
    <div class="stat-card"><span class="stat-number">${d.utilizatori}</span><div class="stat-label">Utilizatori</div></div>
    <div class="stat-card"><span class="stat-number">${d.autori}</span><div class="stat-label">Autori</div></div>
    <div class="stat-card"><span class="stat-number">${d.edituri}</span><div class="stat-label">Edituri</div></div>
    <div class="stat-card"><span class="stat-number">${d.imprumuturi_active}</span><div class="stat-label">Împrumutate</div></div>
    <div class="stat-card"><span class="stat-number">${d.total_incasari} RON</span><div class="stat-label">Încasări</div></div>
  `;
  if (d.tipuri) {
    document.getElementById('stats-tipuri').innerHTML = Object.entries(d.tipuri).map(([tip,nr])=>`
      <div style="display:flex;justify-content:space-between;padding:8px 0;border-bottom:1px solid var(--border)">
        <span style="color:var(--text2)">${tip}</span>
        <span class="badge badge-gold">${nr}</span>
      </div>
    `).join('');
  }
}

// ---- PROFIL ----
async function loadProfil() {
  const d = await api('GET', '/api/utilizator?id=' + userInfo.id);
  if (!d) return;
  document.getElementById('profil-info').innerHTML = `
    <div style="line-height:2;font-size:0.9rem">
      <div><span style="color:var(--text2)">Nume:</span> <span style="color:var(--cream)">${d.numeComplet}</span></div>
      <div><span style="color:var(--text2)">ID:</span> <span style="color:var(--cream)">${d.id}</span></div>
      <div><span style="color:var(--text2)">Tip:</span> <span class="badge badge-gold">${d.tip}</span></div>
      <div><span style="color:var(--text2)">Contact:</span> <span style="color:var(--cream)">${d.contact||'—'}</span></div>
      <div><span style="color:var(--text2)">Împrumuturi:</span> <span style="color:var(--cream)">${d.nrImprumuturi}/${d.limita}</span></div>
      <div><span style="color:var(--text2)">Taxe:</span> <span style="color:${d.taxe>0?'#e07070':'var(--cream)'}">${d.taxe} RON</span></div>
    </div>
  `;
}

async function schimbaParola() {
  const veche = document.getElementById('parola-veche').value;
  const noua = document.getElementById('parola-noua').value;
  const conf = document.getElementById('parola-confirm').value;
  const msg = document.getElementById('parola-msg');
  if (noua !== conf) { msg.innerHTML = '<div class="alert alert-error">Parolele nu coincid.</div>'; return; }
  if (noua.length < 4) { msg.innerHTML = '<div class="alert alert-error">Parola prea scurtă.</div>'; return; }
  const d = await api('POST', '/api/schimba-parola', {id: userInfo.id, parola_veche: veche, parola_noua: noua});
  msg.innerHTML = `<div class="alert ${d.ok ? 'alert-success' : 'alert-error'}">${d.mesaj}</div>`;
}

// ---- ISTORIC ----
async function loadIstoric() {
  const d = await api('GET', '/api/istoric?id=' + userInfo.id);
  const el = document.getElementById('istoric-content');
  if (!d || !d.istoric || d.istoric.length === 0) {
    el.innerHTML = '<p style="color:var(--text2);font-style:italic">Nicio carte înregistrată încă.</p>';
    return;
  }
  el.innerHTML = `<table><thead><tr><th>Carte</th><th>ISBN</th><th>Data</th><th>Rating</th></tr></thead>
    <tbody>${d.istoric.map(i=>`<tr>
      <td style="color:var(--cream)">${i.titlu}</td>
      <td style="color:var(--text2);font-size:0.8rem">${i.isbn}</td>
      <td style="color:var(--text2)">${i.data}</td>
      <td style="color:var(--gold)">${'★'.repeat(i.rating||0)}${'☆'.repeat(5-(i.rating||0))}</td>
    </tr>`).join('')}</tbody></table>`;
}

// ---- WISHLIST ----
function renderWishlist() {
  const el = document.getElementById('wishlist-content');
  if (wishlist.length === 0) {
    el.innerHTML = '<p style="color:var(--text2);font-style:italic">Lista ta de lectură este goală.</p>';
    return;
  }
  el.innerHTML = wishlist.map((isbn, i) => `
    <div class="wishlist-item">
      <span style="color:var(--cream)">${isbn}</span>
      <button class="btn btn-danger" style="padding:4px 10px;font-size:0.75rem" onclick="removeWishlist(${i})">Șterge</button>
    </div>
  `).join('');
}

function adaugaWishlist() {
  const isbn = document.getElementById('wish-isbn').value.trim();
  if (!isbn) return;
  if (!wishlist.includes(isbn)) {
    wishlist.push(isbn);
    localStorage.setItem('wishlist_' + userInfo.id, JSON.stringify(wishlist));
  }
  document.getElementById('wish-isbn').value = '';
  renderWishlist();
}

function removeWishlist(i) {
  wishlist.splice(i, 1);
  localStorage.setItem('wishlist_' + userInfo.id, JSON.stringify(wishlist));
  renderWishlist();
}

// ---- RECOMANDARI ----
async function getRecomandari(gen) {
  const d = await api('GET', '/api/recomandari?gen=' + encodeURIComponent(gen));
  const el = document.getElementById('rec-rezultate');
  if (!d || !d.carti || d.carti.length === 0) {
    el.innerHTML = '<div class="alert alert-info">Nu am găsit recomandări pentru acest gen.</div>';
    return;
  }
  el.innerHTML = `<div class="card"><div class="card-title">Recomandări — ${gen}</div>
    <div class="table-wrap"><table>
      <thead><tr><th>Titlu</th><th>Autor</th><th>An</th><th>Disponibile</th></tr></thead>
      <tbody>${d.carti.map(c=>`<tr>
        <td><strong style="color:var(--cream)">${c.titlu}</strong></td>
        <td style="color:var(--text2)">${c.autori}</td>
        <td>${c.an}</td>
        <td><span class="${c.disponibile>0?'badge badge-green':'badge badge-red'}">${c.disponibile}</span></td>
      </tr>`).join('')}</tbody>
    </table></div></div>`;
}

// ---- ANUNTURI ----
async function loadAnunturi() {
  const d = await api('GET', '/api/anunturi');
  const el = document.getElementById('anunturi-list');
  const isStaff = userInfo && userInfo.tip === 'STAFF';
  if (isStaff) document.getElementById('card-adauga-anunt').style.display = 'block';
  if (!d || !d.anunturi || d.anunturi.length === 0) {
    el.innerHTML = '<div class="alert alert-info">Niciun anunț momentan.</div>';
    return;
  }
  el.innerHTML = d.anunturi.map(a => `
    <div class="anunt">
      <div class="anunt-data">📅 ${a.data}</div>
      <div class="anunt-titlu">${a.titlu}</div>
      <div class="anunt-text">${a.text}</div>
    </div>
  `).join('');
}

async function adaugaAnunt() {
  const titlu = document.getElementById('anunt-titlu-input').value.trim();
  const text = document.getElementById('anunt-text-input').value.trim();
  const data = document.getElementById('anunt-data-input').value.trim();
  if (!titlu || !text) return;
  const d = await api('POST', '/api/anunturi', {titlu, text, data});
  if (d.ok) {
    document.getElementById('anunt-titlu-input').value = '';
    document.getElementById('anunt-text-input').value = '';
    document.getElementById('anunt-data-input').value = '';
    loadAnunturi();
  }
}

// ---- ADD CARTE (modal) ----
async function adaugaCarte() {
  const body = {
    isbn: document.getElementById('m-isbn').value.trim(),
    titlu: document.getElementById('m-titlu').value.trim(),
    autor_nume: document.getElementById('m-autor-nm').value.trim(),
    autor_prenume: document.getElementById('m-autor-pr').value.trim(),
    editura: document.getElementById('m-editura').value.trim(),
    an: parseInt(document.getElementById('m-an').value)||2024,
    tip: document.getElementById('m-tip').value,
    gen: document.getElementById('m-gen').value.trim(),
    pagini: parseInt(document.getElementById('m-pagini').value)||0,
    pret: parseFloat(document.getElementById('m-pret').value)||0
  };
  const d = await api('POST', '/api/carti', body);
  const msg = document.getElementById('m-carte-msg');
  msg.innerHTML = `<div class="alert ${d.ok ? 'alert-success' : 'alert-error'}">${d.mesaj}</div>`;
  if (d.ok) { setTimeout(()=>closeModal('modal-adauga-carte'), 1500); loadCarti(); }
}

// ---- ADD USER (modal) ----
function updateUserForm() {
  const tip = document.getElementById('u-tip').value;
  document.getElementById('u-extra-student').style.display = tip === 'Student' ? 'block' : 'none';
}

async function adaugaUser() {
  const tip = document.getElementById('u-tip').value;
  const body = {
    id: document.getElementById('u-id').value.trim(),
    nume: document.getElementById('u-nm').value.trim(),
    prenume: document.getElementById('u-pr').value.trim(),
    contact: document.getElementById('u-cont').value.trim(),
    parola: document.getElementById('u-parola').value,
    tip,
    an: 2024, luna: 1
  };
  if (tip === 'Student') {
    body.facultate = document.getElementById('u-fac').value.trim();
    body.an_studiu = parseInt(document.getElementById('u-an-st').value)||1;
    body.matricol = document.getElementById('u-matr').value.trim();
  }
  const d = await api('POST', '/api/utilizatori', body);
  const msg = document.getElementById('u-msg');
  msg.innerHTML = `<div class="alert ${d.ok ? 'alert-success' : 'alert-error'}">${d.mesaj}</div>`;
  if (d.ok) { setTimeout(()=>closeModal('modal-adauga-user'), 1500); loadUtilizatori(); }
}

// ---- MODAL ----
function showModal(id) { document.getElementById(id).classList.add('open'); }
function closeModal(id) { document.getElementById(id).classList.remove('open'); }
document.querySelectorAll('.modal-overlay').forEach(m => {
  m.addEventListener('click', e => { if (e.target === m) m.classList.remove('open'); });
});

// ---- CHATBOT ----
function toggleChat() {
  document.getElementById('chatbot-box').classList.toggle('open');
}

async function sendChat() {
  const inp = document.getElementById('chat-input');
  const msg = inp.value.trim();
  if (!msg) return;
  inp.value = '';
  const msgs = document.getElementById('chat-messages');
  msgs.innerHTML += `<div class="msg msg-user">${msg}</div>`;
  msgs.scrollTop = msgs.scrollHeight;
  const d = await api('POST', '/api/chat', {mesaj: msg, id_user: userInfo?.id || ''});
  msgs.innerHTML += `<div class="msg msg-bot">${d.raspuns || '...'}</div>`;
  msgs.scrollTop = msgs.scrollHeight;
}
</script>
</body>
</html>)HTML";
}

// ===================================================================
// Clasa Server
// ===================================================================
class Server
{
private:
    Biblioteca&        bib;
    httplib::Server    srv;
    std::vector<std::map<string,string>> anunturi;
    // istoric citite: id_user -> vector<{isbn, titlu, data, rating}>
    std::map<string, std::vector<std::map<string,string>>> istoricCitite;

public:
    explicit Server(Biblioteca& b) : bib(b)
    {
        initAnunturi();
        setupRoutes();
    }

    void porneste(int port = 8080)
    {
        std::cout << "\n[Server] Pornit pe http://localhost:" << port << "\n";
        std::cout << "[Server] Deschide browserul la http://localhost:" << port << "\n\n";

        // Deschide browserul automat
        std::thread([port](){
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            string cmd = "xdg-open http://localhost:" + std::to_string(port) +
                         " 2>/dev/null || start http://localhost:" + std::to_string(port);
            system(cmd.c_str());
        }).detach();

        srv.listen("0.0.0.0", port);
    }

private:

    void initAnunturi()
    {
        anunturi.push_back({
            {"titlu","Săptămâna Cărții 2025"},
            {"text","Vă invităm la evenimentele din cadrul Săptămânii Cărții: lansări, dezbateri și expoziții tematice în sala de lectură principală."},
            {"data","15-20 Iunie 2025"}
        });
        anunturi.push_back({
            {"titlu","Colecție Nouă — Informatică"},
            {"text","Biblioteca a achiziționat 50 de titluri noi de informatică și inteligență artificială. Disponibile de acum în sala Tehnica."},
            {"data","1 Mai 2025"}
        });
        anunturi.push_back({
            {"titlu","Program Extins de Vară"},
            {"text","În perioada iulie-august, biblioteca va funcționa cu program prelungit: 08:00-22:00 în zilele lucrătoare."},
            {"data","Iulie — August 2025"}
        });
        anunturi.push_back({
            {"titlu","Club de Lectură"},
            {"text","Lansăm clubul de lectură al bibliotecii! Întâlniri bilunar, vineri la 18:00. Prima carte: Nostalgia de Mircea Cărtărescu."},
            {"data","Vineri, 6 Iunie 2025"}
        });
    }

    // ---------------------------------------------------------------
    // Helper: returneaza utilizatorul din token
    // ---------------------------------------------------------------
    Utilizator* getUserDinReq(const httplib::Request& req)
    {
        string id = getIdDinToken(req);
        if (id.empty()) return nullptr;
        return bib.gasesteUtilizator(id);
    }

    bool esteStaff(const httplib::Request& req)
    {
        Utilizator* u = getUserDinReq(req);
        if (!u) return false;
        return u->getTip() == TipUtilizator::STAFF;
    }

    // ---------------------------------------------------------------
    // Helper: JSON carte
    // ---------------------------------------------------------------
    string carteToJSON(Carte* c)
    {
        string autoriStr;
        for (Autor* a : c->getAutori()) {
            if (!autoriStr.empty()) autoriStr += ", ";
            autoriStr += a->getNumeComplet();
        }
        string numeEd = c->getEditura() ? c->getEditura()->getNume() : "";
        std::ostringstream o;
        o << "{"
          << JSON::str("isbn", c->getIsbn()) << ","
          << JSON::str("titlu", c->getTitlu()) << ","
          << JSON::str("autori", autoriStr) << ","
          << JSON::str("tip", c->getTipCarte()) << ","
          << JSON::str("gen", c->getGen()) << ","
          << JSON::str("editura", numeEd) << ","
          << JSON::num("an", c->getAnAparitie()) << ","
          << JSON::num("disponibile", c->nrExemplareDisponibile()) << ","
          << JSON::num("total", c->nrExemplareTotal()) << ","
          << JSON::str("serie", c->getSerie()) << ","
          << JSON::num("pret", c->getPretCatalog())
          << "}";
        return o.str();
    }

    // ---------------------------------------------------------------
    // Helper: JSON utilizator
    // ---------------------------------------------------------------
    string userToJSON(Utilizator* u)
    {
        std::ostringstream o;
        o << "{"
          << JSON::str("id", u->getId()) << ","
          << JSON::str("numeComplet", u->getNumeComplet()) << ","
          << JSON::str("tip", u->getTipNume()) << ","
          << JSON::str("contact", u->getContact()) << ","
          << JSON::num("nrImprumuturi", u->getNrImprumuturi()) << ","
          << JSON::num("limita", u->getLimitaImprumuturi()) << ","
          << JSON::num("taxe", u->getTaxeAcumulate())
          << "}";
        return o.str();
    }

    // ---------------------------------------------------------------
    // CORS headers
    // ---------------------------------------------------------------
    void addCORS(httplib::Response& res)
    {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Headers", "Content-Type, Authorization");
    }

    // ---------------------------------------------------------------
    // Parse JSON simplu (pentru body-uri mici)
    // ---------------------------------------------------------------
    std::map<string,string> parseJSON(const string& body)
    {
        std::map<string,string> result;
        string s = body;
        // Elimina { }
        size_t start = s.find('{');
        size_t end = s.rfind('}');
        if (start == string::npos || end == string::npos) return result;
        s = s.substr(start+1, end-start-1);

        // Parcurge perechi "key":"value"
        size_t pos = 0;
        while (pos < s.size()) {
            // Gaseste cheia
            size_t ks = s.find('"', pos);
            if (ks == string::npos) break;
            size_t ke = s.find('"', ks+1);
            if (ke == string::npos) break;
            string key = s.substr(ks+1, ke-ks-1);
            pos = ke+1;

            // Gaseste :
            size_t colon = s.find(':', pos);
            if (colon == string::npos) break;
            pos = colon+1;

            // Sari spatii
            while (pos < s.size() && s[pos]==' ') pos++;

            string val;
            if (pos < s.size() && s[pos]=='"') {
                // String value
                size_t vs = pos+1;
                size_t ve = vs;
                while (ve < s.size()) {
                    if (s[ve]=='\\' && ve+1<s.size()) { ve+=2; continue; }
                    if (s[ve]=='"') break;
                    ve++;
                }
                val = s.substr(vs, ve-vs);
                // Unescape
                string unesc;
                for (size_t i=0;i<val.size();i++) {
                    if (val[i]=='\\' && i+1<val.size()) {
                        if (val[i+1]=='"') { unesc+='"'; i++; }
                        else if (val[i+1]=='n') { unesc+='\n'; i++; }
                        else { unesc+=val[i+1]; i++; }
                    } else unesc+=val[i];
                }
                val=unesc;
                pos = ve+1;
            } else {
                // Numeric/bool
                size_t ve = pos;
                while (ve < s.size() && s[ve]!=',' && s[ve]!='}' && s[ve]!=']') ve++;
                val = s.substr(pos, ve-pos);
                // Trim
                while (!val.empty() && val.back()==' ') val.pop_back();
                pos = ve;
            }
            result[key] = val;
            // Sari pana la urmatoarea virgula
            size_t comma = s.find(',', pos);
            pos = (comma==string::npos) ? s.size() : comma+1;
        }
        return result;
    }

    // ---------------------------------------------------------------
    // SETUP ROUTES
    // ---------------------------------------------------------------
    void setupRoutes()
    {
        // ---- Serveste HTML ----
        srv.Get("/", [](const httplib::Request&, httplib::Response& res){
            res.set_content(getHTML(), "text/html; charset=utf-8");
        });

        // ---- OPTIONS (CORS) ----
        srv.Options(".*", [this](const httplib::Request&, httplib::Response& res){
            addCORS(res);
            res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
            res.status = 204;
        });

        // ---- LOGIN ----
        srv.Post("/api/login", [this](const httplib::Request& req, httplib::Response& res){
            addCORS(res);
            auto p = parseJSON(req.body);
            string id = p["id"];
            string parola = p["parola"];
            Utilizator* u = bib.gasesteUtilizator(id);
            if (!u || !u->verificaParola(parola)) {
                res.set_content("{\"ok\":false,\"mesaj\":\"ID sau parolă incorectă.\"}", "application/json");
                return;
            }
            string tok = genToken(id);
            sesiuniActive[tok] = id;
            std::ostringstream o;
            o << "{\"ok\":true,\"token\":\"" << tok << "\","
              << "\"user\":{" << JSON::str("id",u->getId()) << ","
              << JSON::str("numeComplet",u->getNumeComplet()) << ","
              << JSON::str("tip",u->getTipNume()) << "}}";
            res.set_content(o.str(), "application/json");
        });

        // ---- GET CARTI ----
        srv.Get("/api/carti", [this](const httplib::Request&, httplib::Response& res){
            addCORS(res);
            string json = "[";
            for (int i=0; i<bib.getNrCarti(); i++) {
                if (i) json += ",";
                json += carteToJSON(bib.getCarte(i));
            }
            json += "]";
            res.set_content("{\"carti\":" + json + "}", "application/json");
        });

        // ---- POST CARTI (adauga) ----
        srv.Post("/api/carti", [this](const httplib::Request& req, httplib::Response& res){
            addCORS(res);
            if (!esteStaff(req)) {
                res.set_content("{\"ok\":false,\"mesaj\":\"Acces interzis.\"}", "application/json");
                return;
            }
            auto p = parseJSON(req.body);
            try {
                Autor* a = bib.gasesteOrAdaugaAutor(p["autor_nume"],p["autor_prenume"],"",0,true);
                Editura* e = bib.gasesteOrAdaugaEditura(p["editura"],"","");
                int an = p["an"].empty() ? 2024 : std::stoi(p["an"]);
                int pagini = p["pagini"].empty() ? 0 : std::stoi(p["pagini"]);
                double pret = p["pret"].empty() ? 0 : std::stod(p["pret"]);
                string tip = p["tip"];
                Carte* c = nullptr;
                if (tip=="Fictiune")
                    c = new CarteFictiune(p["isbn"],p["titlu"],{a},e,an,LimbaCartii::ROMANA,TipCoperta::BROSATA,p["gen"],14,pagini,0,""  ,0,pret);
                else if (tip=="Tehnica")
                    c = new CarteTehnica(p["isbn"],p["titlu"],{a},e,an,LimbaCartii::ENGLEZA,TipCoperta::CARTONATA,p["gen"],"Intermediar",false,pagini,0,pret);
                else if (tip=="Educativa")
                    c = new CarteEducativa(p["isbn"],p["titlu"],{a},e,an,LimbaCartii::ROMANA,TipCoperta::BROSATA,p["gen"],"General",0,pagini,0,pret);
                else
                    c = new CarteFictiune(p["isbn"],p["titlu"],{a},e,an,LimbaCartii::ROMANA,TipCoperta::BROSATA,p["gen"],0,pagini,0,"",0,pret);
                bib.adaugaCarte(c);
                Fisiere::salveazaTot(bib);
                res.set_content("{\"ok\":true,\"mesaj\":\"Cartea a fost adăugată.\"}", "application/json");
            } catch (const std::exception& ex) {
                string err = ex.what();
                res.set_content("{\"ok\":false,\"mesaj\":\"" + JSON::esc(err) + "\"}", "application/json");
            }
        });

        // ---- CAUTARE ----
        srv.Get("/api/cauta", [this](const httplib::Request& req, httplib::Response& res){
            addCORS(res);
            string tip = req.get_param_value("tip");
            string q   = req.get_param_value("q");
            std::vector<Carte*> rez;
            if (tip=="titlu")       rez = bib.cautaDupaTitlu(q);
            else if (tip=="autor")  rez = bib.cautaDupaAutor(q);
            else if (tip=="an")     rez = bib.cautaDupaAn(std::stoi(q.empty()?"0":q));
            string json = "[";
            for (size_t i=0;i<rez.size();i++) {
                if (i) json+=",";
                json+=carteToJSON(rez[i]);
            }
            json+="]";
            res.set_content("{\"rezultate\":" + json + "}", "application/json");
        });

        // ---- GET UTILIZATORI ----
        srv.Get("/api/utilizatori", [this](const httplib::Request& req, httplib::Response& res){
            addCORS(res);
            if (!esteStaff(req)) {
                res.set_content("{\"utilizatori\":[]}", "application/json");
                return;
            }
            string json = "[";
            for (int i=0;i<bib.getNrUtilizatori();i++) {
                if (i) json+=",";
                json+=userToJSON(bib.getUtilizator(i));
            }
            json+="]";
            res.set_content("{\"utilizatori\":" + json + "}", "application/json");
        });

        // ---- GET UTILIZATOR BY ID ----
        srv.Get("/api/utilizator", [this](const httplib::Request& req, httplib::Response& res){
            addCORS(res);
            string id = req.get_param_value("id");
            Utilizator* u = bib.gasesteUtilizator(id);
            if (!u) { res.set_content("{}", "application/json"); return; }
            res.set_content(userToJSON(u), "application/json");
        });

        // ---- POST UTILIZATORI (adauga) ----
        srv.Post("/api/utilizatori", [this](const httplib::Request& req, httplib::Response& res){
            addCORS(res);
            if (!esteStaff(req)) {
                res.set_content("{\"ok\":false,\"mesaj\":\"Acces interzis.\"}", "application/json");
                return;
            }
            auto p = parseJSON(req.body);
            try {
                int an = p["an"].empty() ? 2024 : std::stoi(p["an"]);
                int luna = p["luna"].empty() ? 1 : std::stoi(p["luna"]);
                Utilizator* u = nullptr;
                if (p["tip"]=="Student") {
                    int anSt = p["an_studiu"].empty() ? 1 : std::stoi(p["an_studiu"]);
                    u = new UtilizatorStudent(p["id"],p["nume"],p["prenume"],p["contact"],p["parola"],an,luna,p["facultate"],anSt,p["matricol"]);
                } else {
                    u = new UtilizatorBasic(p["id"],p["nume"],p["prenume"],p["contact"],p["parola"],an,luna);
                }
                bib.adaugaUtilizator(u);
                Fisiere::salveazaTot(bib);
                res.set_content("{\"ok\":true,\"mesaj\":\"Utilizatorul a fost adăugat.\"}", "application/json");
            } catch (const std::exception& ex) {
                string err = ex.what();
                res.set_content("{\"ok\":false,\"mesaj\":\"" + JSON::esc(err) + "\"}", "application/json");
            }
        });

        // ---- IMPRUMUT ----
        srv.Post("/api/imprumut", [this](const httplib::Request& req, httplib::Response& res){
            addCORS(res);
            auto p = parseJSON(req.body);
            try {
                int zi = p["zi"].empty() ? 1 : std::stoi(p["zi"]);
                int luna = p["luna"].empty() ? 1 : std::stoi(p["luna"]);
                int an = p["an"].empty() ? 2024 : std::stoi(p["an"]);
                bib.imprumutaCarte(p["id_user"], p["isbn"], zi, luna, an);
                Fisiere::salveazaTot(bib);
                res.set_content("{\"ok\":true,\"mesaj\":\"Împrumut înregistrat cu succes.\"}", "application/json");
            } catch (const std::exception& ex) {
                string err = ex.what();
                res.set_content("{\"ok\":false,\"mesaj\":\"" + JSON::esc(err) + "\"}", "application/json");
            }
        });

        // ---- RETURNARE ----
        srv.Post("/api/returnare", [this](const httplib::Request& req, httplib::Response& res){
            addCORS(res);
            auto p = parseJSON(req.body);
            try {
                int zile = p["zile_intarziere"].empty() ? 0 : std::stoi(p["zile_intarziere"]);
                int rating = p["rating"].empty() ? 0 : std::stoi(p["rating"]);
                string idUser = p["id_user"];
                string cod = p["cod_exemplar"];

                // Gasim ISBN-ul cartii din imprumut
                string isbnCarte;
                for (const auto& imp : bib.getImprumuturi()) {
                    if (imp.codExemplar == cod && imp.idUtilizator == idUser && imp.esteActiv) {
                        isbnCarte = imp.isbnCarte;
                        break;
                    }
                }

                bib.returneazaCarte(idUser, cod, zile);

                // Salvam in istoric
                if (!isbnCarte.empty() && rating > 0) {
                    Carte* c = bib.gasesteCarte(isbnCarte);
                    string titlu = c ? c->getTitlu() : isbnCarte;
                    auto now = std::time(nullptr);
                    char buf[32];
                    std::strftime(buf, sizeof(buf), "%d.%m.%Y", std::localtime(&now));
                    istoricCitite[idUser].push_back({
                        {"isbn", isbnCarte},
                        {"titlu", titlu},
                        {"data", string(buf)},
                        {"rating", std::to_string(rating)}
                    });
                }

                Fisiere::salveazaTot(bib);
                res.set_content("{\"ok\":true,\"mesaj\":\"Returnare înregistrată.\"}", "application/json");
            } catch (const std::exception& ex) {
                string err = ex.what();
                res.set_content("{\"ok\":false,\"mesaj\":\"" + JSON::esc(err) + "\"}", "application/json");
            }
        });

        // ---- INCASARE ----
        srv.Post("/api/incasare", [this](const httplib::Request& req, httplib::Response& res){
            addCORS(res);
            auto p = parseJSON(req.body);
            try {
                double suma = p["suma"].empty() ? 0 : std::stod(p["suma"]);
                bib.incaseazaTaxa(p["id_user"], suma);
                Fisiere::salveazaTot(bib);
                res.set_content("{\"ok\":true,\"mesaj\":\"Taxă încasată.\"}", "application/json");
            } catch (const std::exception& ex) {
                string err = ex.what();
                res.set_content("{\"ok\":false,\"mesaj\":\"" + JSON::esc(err) + "\"}", "application/json");
            }
        });

        // ---- STATISTICI ----
        srv.Get("/api/statistici", [this](const httplib::Request&, httplib::Response& res){
            addCORS(res);
            int imprActive = 0;
            for (const auto& imp : bib.getImprumuturi())
                if (imp.esteActiv) imprActive++;

            // Tipuri
            std::map<string,int> tipuri;
            for (int i=0;i<bib.getNrCarti();i++)
                tipuri[bib.getCarte(i)->getTipCarte()]++;

            string tipuriJson = "{";
            bool first = true;
            for (auto& [t,n] : tipuri) {
                if (!first) tipuriJson+=",";
                tipuriJson += "\"" + t + "\":" + std::to_string(n);
                first=false;
            }
            tipuriJson+="}";

            std::ostringstream o;
            o << "{"
              << JSON::num("carti", bib.getNrCarti()) << ","
              << JSON::num("utilizatori", bib.getNrUtilizatori()) << ","
              << JSON::num("autori", bib.getNrAutori()) << ","
              << JSON::num("edituri", bib.getNrEdituri()) << ","
              << JSON::num("imprumuturi_active", imprActive) << ","
              << JSON::num("total_incasari", (int)bib.getTotalIncasari()) << ","
              << "\"tipuri\":" << tipuriJson
              << "}";
            res.set_content(o.str(), "application/json");
        });

        // ---- SCHIMBA PAROLA ----
        srv.Post("/api/schimba-parola", [this](const httplib::Request& req, httplib::Response& res){
            addCORS(res);
            auto p = parseJSON(req.body);
            Utilizator* u = bib.gasesteUtilizator(p["id"]);
            if (!u) { res.set_content("{\"ok\":false,\"mesaj\":\"Utilizatorul nu există.\"}", "application/json"); return; }
            if (!u->verificaParola(p["parola_veche"])) {
                res.set_content("{\"ok\":false,\"mesaj\":\"Parola veche incorectă.\"}", "application/json"); return;
            }
            u->setParola(p["parola_noua"]);
            Fisiere::salveazaTot(bib);
            res.set_content("{\"ok\":true,\"mesaj\":\"Parola a fost actualizată.\"}", "application/json");
        });

        // ---- ISTORIC ----
        srv.Get("/api/istoric", [this](const httplib::Request& req, httplib::Response& res){
            addCORS(res);
            string id = req.get_param_value("id");
            auto it = istoricCitite.find(id);
            if (it == istoricCitite.end()) {
                res.set_content("{\"istoric\":[]}", "application/json"); return;
            }
            string json = "[";
            for (size_t i=0;i<it->second.size();i++) {
                if (i) json+=",";
                auto& e = it->second[i];
                json += "{" + JSON::str("isbn",e.at("isbn")) + ","
                      + JSON::str("titlu",e.at("titlu")) + ","
                      + JSON::str("data",e.at("data")) + ","
                      + JSON::str("rating",e.at("rating")) + "}";
            }
            json+="]";
            res.set_content("{\"istoric\":" + json + "}", "application/json");
        });

        // ---- RECOMANDARI ----
        srv.Get("/api/recomandari", [this](const httplib::Request& req, httplib::Response& res){
            addCORS(res);
            string gen = req.get_param_value("gen");
            auto rez = bib.cautaDupaTitlu(""); // toate
            // filtram dupa gen in titlu sau tip
            std::vector<Carte*> filtrate;
            string genLower = gen;
            for (char& c : genLower) c = (char)std::tolower((unsigned char)c);
            for (Carte* c : rez) {
                string tipLower = c->getTipCarte();
                for (char& ch : tipLower) ch = (char)std::tolower((unsigned char)ch);
                if (tipLower.find(genLower) != string::npos) {
                    filtrate.push_back(c);
                    if (filtrate.size() >= 20) break;
                }
            }
            // Daca putine rezultate, cauta si in titlu
            if (filtrate.size() < 5) {
                auto byTitlu = bib.cautaDupaTitlu(gen);
                for (Carte* c : byTitlu) {
                    if (filtrate.size() >= 20) break;
                    bool deja = false;
                    for (Carte* f : filtrate) if (f->getIsbn()==c->getIsbn()) { deja=true; break; }
                    if (!deja) filtrate.push_back(c);
                }
            }
            string json = "[";
            for (size_t i=0;i<filtrate.size();i++) {
                if (i) json+=",";
                json+=carteToJSON(filtrate[i]);
            }
            json+="]";
            res.set_content("{\"carti\":" + json + "}", "application/json");
        });

        // ---- ANUNTURI GET ----
        srv.Get("/api/anunturi", [this](const httplib::Request&, httplib::Response& res){
            addCORS(res);
            string json = "[";
            for (size_t i=0;i<anunturi.size();i++) {
                if (i) json+=",";
                json += "{" + JSON::str("titlu",anunturi[i].at("titlu")) + ","
                      + JSON::str("text",anunturi[i].at("text")) + ","
                      + JSON::str("data",anunturi[i].at("data")) + "}";
            }
            json+="]";
            res.set_content("{\"anunturi\":" + json + "}", "application/json");
        });

        // ---- ANUNTURI POST ----
        srv.Post("/api/anunturi", [this](const httplib::Request& req, httplib::Response& res){
            addCORS(res);
            if (!esteStaff(req)) {
                res.set_content("{\"ok\":false,\"mesaj\":\"Acces interzis.\"}", "application/json"); return;
            }
            auto p = parseJSON(req.body);
            anunturi.insert(anunturi.begin(), {{"titlu",p["titlu"]},{"text",p["text"]},{"data",p["data"]}});
            res.set_content("{\"ok\":true}", "application/json");
        });

        // ---- CHATBOT ----
        srv.Post("/api/chat", [this](const httplib::Request& req, httplib::Response& res){
            addCORS(res);
            auto p = parseJSON(req.body);
            string msg = p["mesaj"];
            string idUser = p["id_user"];

            // Lowercase pentru matching
            string msgL = msg;
            for (char& c : msgL) c = (char)std::tolower((unsigned char)c);

            string raspuns;

            if (msgL.find("imprumut") != string::npos || msgL.find("împrumut") != string::npos) {
                raspuns = "Pentru a împrumuta o carte, mergeți la secțiunea Împrumuturi & Returnări și introduceți ID-ul dvs. și ISBN-ul cărții dorite. Aveți nevoie de un exemplar disponibil.";
            } else if (msgL.find("program") != string::npos || msgL.find("orar") != string::npos) {
                raspuns = "Programul bibliotecii: Luni-Vineri 08:00-20:00, Sâmbătă 09:00-14:00, Duminică: Închis.";
            } else if (msgL.find("parola") != string::npos || msgL.find("parolă") != string::npos) {
                raspuns = "Puteți schimba parola din secțiunea Profilul Meu → Schimbă Parola. Aveți nevoie de parola curentă.";
            } else if (msgL.find("cont") != string::npos && msgL.find("nou") != string::npos) {
                raspuns = "Conturile noi se creează de către personalul bibliotecii. Prezentați-vă la ghișeu cu actul de identitate.";
            } else if (msgL.find("wishlist") != string::npos || msgL.find("lista") != string::npos) {
                raspuns = "Lista de Lectură vă permite să salvați cărțile pe care doriți să le citiți. Găsiți secțiunea în meniul din stânga.";
            } else if (msgL.find("tax") != string::npos) {
                raspuns = "Taxa de întârziere este de 1-2 RON/zi în funcție de tipul cărții. Studenții beneficiază de 20% discount. Plata se face la ghișeul bibliotecii.";
            } else if (msgL.find("recoman") != string::npos) {
                raspuns = "Secțiunea Recomandări vă oferă sugestii de cărți pe baza genului preferat. Alegeți un gen și vedeți ce vă recomandăm!";
            } else if (msgL.find("bun") != string::npos || msgL.find("salut") != string::npos || msgL.find("hello") != string::npos) {
                raspuns = "Bună ziua! Sunt asistentul Bibliotecii Universitare Suceava. Vă pot ajuta cu informații despre împrumuturi, programul bibliotecii, contul dvs. sau colecția de cărți.";
            } else if (msgL.find("caut") != string::npos) {
                int total = bib.getNrCarti();
                raspuns = "Colecția noastră conține " + std::to_string(total) + " titluri. Folosiți secțiunea Căutare pentru a găsi cărți după titlu, autor sau ISBN.";
            } else if (msgL.find("multumesc") != string::npos || msgL.find("mulțumesc") != string::npos) {
                raspuns = "Cu plăcere! Nu ezitați să reveniți dacă mai aveți întrebări. Lectură plăcută! 📚";
            } else {
                raspuns = "Înțeleg întrebarea dvs. despre \"" + msg + "\". Pentru asistență personalizată, vă rog să contactați personalul bibliotecii la biblioteca@usv.ro sau să vizitați ghișeul principal. Pot să vă ajut cu informații despre împrumuturi, program, sau colecția de cărți.";
            }

            res.set_content("{\"raspuns\":\"" + JSON::esc(raspuns) + "\"}", "application/json");
        });
    }
};

#endif // SERVER_H