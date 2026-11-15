# Saitama com ponte Bitchat

Este repositório é um derivado do [Saitama](https://github.com/868meshbot/Saitama) (licença
GPL-3.0-or-later) com a ponte Bitchat de
[EduChacon/Meshcore-Bitchat](https://github.com/EduChacon/Meshcore-Bitchat) embutida. O Saitama
continua sendo o sistema do aparelho, com tela, toque, teclado e esfera; a ponte leva o texto
público do aplicativo Bitchat para um canal do MeshCore e de volta.

**Estado em 2026-11-15: compila para as duas placas; nunca foi ligado em aparelho.** A ponte
funcionou em um Heltec V3 com o MeshCore original (versão `bitchat0.1`). A ligação dela ao Saitama,
descrita aqui, não foi ensaiada.

## Arquivos

| Aparelho                                | Ambiente                | Arquivo                                        |
| --------------------------------------- | ----------------------- | ---------------------------------------------- |
| LilyGo T-Deck e T-Deck Plus             | `t-deck-bitchat`        | `saitama-t-deck-plus-bitchat-<versão>`         |
| M5Stack Cardputer ADV com Cap LoRa-1262 | `cardputer-adv-bitchat` | `saitama-cardputer-adv-bitchat-<versão>`       |

Cada um tem duas formas:

- `…-merged.bin`: aparelho novo ou vindo de outro sistema. Gravar no endereço `0x0` depois de
  apagar a memória. Tudo o que havia no aparelho é perdido.
- `….bin`: aparelho que já roda o Saitama. Gravar no endereço `0x10000`; contatos, canais e
  ajustes são mantidos.

O chip é `esp32-s3`. A memória tem 16 MB no T-Deck e 8 MB no Cardputer ADV.

Os ambientes `t-deck` e `cardputer-adv`, sem a ponte, continuam como no Saitama original.

## Primeiro uso

1. **Rádio.** Em instalação nova, estas versões já saem na convenção da comunidade MeshCore
   Brasil: 923,125 MHz, largura de 62,5 kHz, SF 8, CR 4/8 e _path hash_ de 2 bytes, gravados como
   valores personalizados (_Settings_ > _Radio Mode_ mostra _Custom_). Um aparelho que já tinha
   ajustes salvos, na memória ou no cartão SD, mantém os dele: confira antes de transmitir. Para
   falar com outros rádios, os quatro valores precisam ser iguais aos deles.
2. **Bluetooth.** Em instalação nova ele já vem ligado nesta versão. Se os ajustes forem
   restaurados do cartão SD com o Bluetooth desligado, ligue-o em _Settings_.
3. **Canal.** A ponte cria sozinha o canal `bitchat` (aba `bchat`) na primeira partida, se houver
   uma das nove posições de canal livre. É o mesmo canal `#bitchat` do MeshCore.
4. **Bitchat.** Abra o aplicativo Bitchat em um telefone próximo e espere até dois minutos.

A partir daí:

- o que alguém escreve no `#mesh` do Bitchat aparece no canal `bitchat` do aparelho e sai pelo
  LoRa como `apelido: texto`;
- o que é escrito no canal `bitchat`, no aparelho ou por outro rádio MeshCore, chega aos telefones
  Bitchat próximos como `[MC nome] texto`;
- texto trazido ao Bitchat por uma ponte Meshtastic (`[MT nome] texto`) também sai no canal, uma
  vez só, como `MT nome: texto`.

O aplicativo MeshCore no telefone continua podendo conectar. O PIN é o do próprio Saitama
(_Settings_ > _Bluetooth PIN_). Por causa da troca da pilha Bluetooth, um telefone já pareado com o
Saitama original precisa esquecer o aparelho e parear de novo.

## Estado e comandos

- **Tela _Signal_, seção _HARDWARE_:** a linha `Bitchat:` mostra o estado da ponte.
- **`!bridge`**, enviado em qualquer canal do aparelho, mostra o relatório da ponte na própria
  conversa (remetente `bridge`) e não é transmitido.
- `!bridge on`, `!bridge off`: liga e desliga a ponte.
- `!bridge local`: só Bluetooth, sem LoRa. `!bridge lora`: volta a usar o canal.
- `!bridge link off`, `!bridge link on`: desliga e liga a passagem do texto vindo de pontes
  Meshtastic.
- `!bridge economy on`, `!bridge economy off`: liga e desliga o modo econômico da ponte, que vem
  desligado; a escolha fica gravada.

## O que muda em relação ao Saitama original

a) **Pilha Bluetooth NimBLE** no lugar da original, compartilhada entre o aplicativo MeshCore e o
serviço do Bitchat.

b) **O aplicativo _BT Foxhunt_ fica fora** destas versões: ele foi escrito para a outra pilha. O
ícone permanece no lançador do T-Deck e não faz nada.

c) **Sem repouso do processador enquanto o Bluetooth estiver ligado.** A ponte atende os telefones
com a tela apagada, e as conexões não sobreviveriam ao repouso. A bateria dura menos; com o
Bluetooth desligado o aparelho repousa como antes. O modo econômico, opcional e desligado de
fábrica (`!bridge economy on`), faz a ponte anunciar-se cerca de uma vez por segundo depois de três
minutos sem nenhum telefone Bitchat; isso reduz o gasto em espera, sem devolver o repouso, e nesse
ritmo tanto o Bitchat quanto o aplicativo MeshCore podem demorar mais para encontrar o aparelho.
Quando a ponte não estiver em uso, `!bridge off` ou desligar o Bluetooth nos ajustes poupa mais.

d) **O MeshCore embutido** (`lib/MeshCore`) aponta para `EduChacon/Meshcore-Bitchat`, que é o
MeshCore 1.18.0 com os arquivos da ponte. As fontes do MeshCore em si são as mesmas.

e) **Estas versões são compiladas em C++17**, exigido pela ponte, e usam a biblioteca
`NimBLE-Arduino` 1.4.3.

f) **Rádio de fábrica no padrão brasileiro** (item 1 do primeiro uso), em vez do europeu. A
potência não muda (22 dBm). O cumprimento das regras da Anatel é do usuário.

g) A ponte guarda 16 mensagens recentes entre reinícios, em vez de 64, para ocupar menos da área de
ajustes do aparelho.

## O que não se sabe

a) Se inicia e funciona: nada foi ligado.

b) **Área de ajustes (NVS).** São 16 KB, divididos entre o Saitama e a ponte. Se faltar espaço, a
ponte mostra `Storage error`; não se sabe se o Saitama também seria afetado.

c) **Memória no Cardputer ADV.** Ele não tem PSRAM. Se faltar memória, a ponte mostra
`Low memory: bridge OFF` e o restante deve seguir funcionando.

d) O consumo com o Bluetooth ligado e a tela apagada.

e) Se o aplicativo MeshCore encontra e pareia o aparelho com a nova pilha do mesmo modo que antes.

Se algo não funcionar, grave o arquivo sem a ponte (ambientes `t-deck` ou `cardputer-adv`, ou o
Saitama original) e relate o que apareceu na linha `Bitchat:` e no `!bridge`.

## Compilação

```bash
git submodule update --init --recursive
```

```bash
pio run -e t-deck-bitchat
```

```bash
pio run -e cardputer-adv-bitchat
```

Os testes da ponte em computador ficam no repositório `EduChacon/Meshcore-Bitchat`
(`tools/bitchat/run_tests.py`).
