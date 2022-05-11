# The Task (13)
Kasko draudimas/autoservisas (ADT: prioritetinė eilė, ilgas sveikas skaičius).

# Procesas 1.
Klientas draudžiasi mašiną kasko draudimu įmonėje, kuri turi bendradarbiavimo sutartį su autoservisu. Tokiu atveju frančizė (minimalus kliento sumokamas mokestis įvykus avarijai, kurį jis turi sumokėti pats) yra A litų dydžio, iš kurių A1 atitenka servisui dėl bendradarbiavimo sutarties kaip priedas, ir klientas laikomas VIP klientu. Tokie klientai servise turi pirmumo teisę, ir jų mašinos yra tvarkomos pirmiausiai (jeigu reikia dirbant netgi viršvalandžius - VIP kliento mašina turi būti pradedama tvarkyti nuo pristatymo akimirkos nenutrūkstamai iki pat jos sutvarkymo, t.y. per vieną dieną). Už viršvalandžius darbuotojams reikia mokėti dvigubai.

# Procesas 2.
Klientas draudžiasi paprastu kasko draudimu, kurio frančizė yra B litų (B=A-A1) ir servisas už tai papildomų pinigų negauna, bet nereikia dirbti ir viršvalandžių, kurie kainuoja brangiau.

Pamodeliuoti, kokia verslo logika servisui naudingiausia: turėti kuo daugiau bendradarbiavimo sutarčių, ar dirbti visai be jų.

# Modelio parametrai:
minėti dydžiai: A, A1 ir B. Taip pat: U – serviso darbuotojo valandinė alga, K - darbuotojų skaičius.  Kiti naudotini dydžiai: T1 - tikimybė procentais, kad mašiną pristatys VIP klientas, T2 - tikimybė procentais, kad mašiną pristatys paprastas klientas, TR - atsitiktinis dydis valandomis, kurio reikia vienam darbuotojui sutvarkyti atvežtą mašiną (tarkime, jog 1<= TR <=5*K).
