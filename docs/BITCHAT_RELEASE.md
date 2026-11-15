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
- Um telefone já pareado com o Saitama original precisa parear de novo.

Guia completo: [docs/BITCHAT.md](https://github.com/EduChacon/Saitama-mesh---BC-/blob/main/docs/BITCHAT.md).
