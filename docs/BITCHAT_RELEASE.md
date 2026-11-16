# Saitama + Bitchat

Saitama (sistema para T-Deck e Cardputer ADV sobre o MeshCore) com a ponte Bitchat embutida.
**Versão experimental: compila para as duas placas e nunca foi ligada em aparelho.**

## Arquivos

**Confira o nome do seu aparelho antes de gravar.**

- `saitama-t-deck-plus-bitchat-…`: LilyGo T-Deck e T-Deck Plus (16 MB).
- `saitama-cardputer-adv-bitchat-…`: M5Stack Cardputer ADV com Cap LoRa-1262 (8 MB).
- `…-merged.bin`: aparelho novo ou vindo de outro sistema; apagar a memória e gravar em `0x0`.
- `….bin`: aparelho que já roda o Saitama; gravar em `0x10000`, mantendo os dados.
- `SHA256SUMS`: somas de conferência.

## O que faz

- Texto público do `#mesh` do Bitchat sai no canal `bitchat` do MeshCore como `apelido: texto`.
- Texto do canal `bitchat` chega aos telefones Bitchat próximos como `[MC nome] texto`.
- Texto trazido por uma ponte Meshtastic–Bitchat (`[MT nome] texto`) também sai no canal.
- A ponte cria o canal sozinha; `!bridge` em qualquer canal mostra o estado.

## Avisos

- **Rádio:** em instalação nova, sai na convenção da comunidade MeshCore Brasil (923,125 MHz,
  62,5 kHz, SF 8, CR 4/8, _path hash_ de 2 bytes). Um aparelho com ajustes já salvos mantém os
  dele; confira antes de transmitir.
- O aplicativo _BT Foxhunt_ não faz parte destas versões.
- Com o Bluetooth ligado o aparelho não repousa, e a bateria dura menos.
- **O modo econômico da ponte passou a ser opcional e vem desligado** (`!bridge economy on` liga,
  `!bridge economy off` desliga; a escolha fica gravada). Na versão anterior ele era automático.
  Ligado, sem telefone Bitchat por três minutos a ponte anuncia-se mais devagar, e tanto o Bitchat
  quanto o aplicativo MeshCore podem demorar mais para encontrar o aparelho.
- Um telefone já pareado com o Saitama original precisa parear de novo.

## Novidade desta versão

- **Funções da casa** (ponte MeshCore `bitchat0.11`), por comando no aparelho ou no `#mesh` do
  Bitchat: `!bridge prefix on`/`off`, `!ponte recado <texto>`, `!ponte bateria` (com aviso de
  bateria baixa), `!ponte radios`, `!ponte sos <texto>` (com a posição do GPS, se houver) e
  `!ponte teste`. Só simuladas e compiladas; o código passou por duas revisões independentes, e
  as falhas achadas foram corrigidas antes da publicação.

## Da versão anterior

- **Menu de ajustes:** linhas **Bitchat** (modo da ponte) e **Bitchat saver** (modo econômico),
  sem precisar dos comandos.
- **Histórico, segunda parte:** a ponte guarda também o que os telefones escrevem no `#mesh` perto
  do aparelho, para quem chega depois (só aparece para quem já conheceu o autor).
- Das versões anteriores: `!ponte quem` (nomes ouvidos no LoRa), histórico do texto do LoRa e
  `!ponte guia`.
