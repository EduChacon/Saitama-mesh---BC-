# Saitama com ponte Bitchat

Este repositório é um derivado do [Saitama](https://github.com/868meshbot/Saitama) (licença
GPL-3.0-or-later) com a ponte Bitchat de
[EduChacon/Meshcore-Bitchat](https://github.com/EduChacon/Meshcore-Bitchat) embutida. O Saitama
continua sendo o sistema do aparelho, com tela, toque, teclado e esfera; a ponte leva o texto
público do aplicativo Bitchat para um canal do MeshCore e de volta.

**Estado em 2026-11-15: compila para as duas placas; nunca foi ligado em aparelho.** A ponte
funcionou em um Heltec V3 com o MeshCore original (versão `bitchat0.1`). A ligação dela ao Saitama,
descrita aqui, não foi ensaiada.

> **Cardputer ADV: não use a versão com ponte por enquanto.** Ensaiada em aparelho em 2026-11-16, a
> `saitama-cardputer-adv-bitchat` fica com cerca de 4 KB de memória livre: os ajustes travam ao abrir,
> e a ponte não consegue iniciar (o canal `bitchat` não aparece). O Cardputer não tem memória extra
> (PSRAM), e o Bluetooth ligado, que a ponte exige, já deixa o Saitama no limite. Para destravar sem
> regravar: no cartão SD, em `/ops/settings.json`, trocar `"bluetooth": true` por `"bluetooth": false`.
> Para ter a ponte no Cardputer, use o firmware MeshCore com ponte
> ([`M5Stack_Cardputer_ADV_companion_radio_ble_bitchat`](https://github.com/EduChacon/Meshcore-Bitchat/releases)).
> A versão do T-Deck Plus não é afetada.

## Arquivos

| Aparelho                                | Ambiente                | Arquivo                                  |
| --------------------------------------- | ----------------------- | ---------------------------------------- |
| LilyGo T-Deck e T-Deck Plus             | `t-deck-bitchat`        | `saitama-t-deck-plus-bitchat-<versão>`   |
| M5Stack Cardputer ADV com Cap LoRa-1262 | `cardputer-adv-bitchat` | `saitama-cardputer-adv-bitchat-<versão>` |

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
- **Histórico para quem chega depois:** o texto que vem do LoRa, e também o que os telefones
  escrevem no `#mesh` perto do aparelho, é guardado mesmo sem telefone conectado (as últimas 12
  mensagens, por até seis horas, só na memória). O telefone que chega recebe o que falta, no
  trecho "ouvido aqui antes" do Bitchat; mensagens de outros telefones só aparecem para quem já
  conheceu o autor. `!bridge` mostra `Kept N`.
- **No menu de ajustes:** a linha **Bitchat** alterna entre `Off`, `Bitchat + LoRa` e
  `Bitchat only`; a linha **Bitchat saver** liga e desliga o modo econômico. A ponte guarda as
  duas escolhas.
- `!ponte quem` (ou `!bridge who`, em inglês): lista os nomes ouvidos no canal LoRa nas últimas
  seis horas. Vale também no `#mesh` do Bitchat, cujo `/who` só mostra a malha Bluetooth.
- `!ponte guia` (ou `!bridge guide`, em inglês): explica a ponte em quatro mensagens curtas. Vale
  também no `#mesh` do Bitchat, para quem só usa o Bitchat; ali sai no máximo uma vez a cada 30
  segundos.
- **Funções da casa** (ponte `bitchat0.11`), no aparelho ou no `#mesh` do Bitchat:
  `!bridge prefix on`/`off` (só o texto iniciado por `!lora` vai ao LoRa; só no aparelho),
  `!ponte recado <texto>` (recado entregue uma vez a cada 12 h a cada telefone que chega; qualquer
  pessoa perto do aparelho pode trocá-lo), `!ponte bateria` (e aviso de bateria baixa no `#mesh`),
  `!ponte radios` (contatos com atividade nas últimas 24 h; só no aparelho, porque inclui com quem
  o dono troca mensagens privadas), `!ponte sos <texto>` (pedido de socorro ao LoRa; digitado no
  aparelho, leva a posição do GPS, quando houver; pedido pelo Bitchat, só se a opção de compartilhar
  a localização estiver ligada ou se `!bridge position on` tiver sido enviado no aparelho, próprio
  para trilha; a posição vai para todos os que têm o canal) e
  `!ponte teste` (teste de alcance com as outras pontes). Descrição completa no
  [guia da ponte MeshCore](https://github.com/EduChacon/Meshcore-Bitchat/blob/main/docs/bitchat/README.md#funções-da-casa-a-partir-da-bitchat011).
  A bateria é lida direto no divisor de tensão, como faz o próprio aparelho. No T-Deck Plus o GPS
  já fica ligado e acerta o relógio; a ponte não mexe nele. As respostas da ponte (remetente
  `bridge`) não são gravadas no cartão SD, mesmo com o histórico de mensagens ligado. Ao gerar uma
  identidade nova para o aparelho, a ponte também passa a ter identidade nova. O recado só é trocado
  por um telefone ligado diretamente ao aparelho.
- **Pagamentos Cashu pelo LoRa** (ponte `bitchat0.20` em diante): um token Cashu colado no chat
  público do Bitchat perto de uma ponte é levado pelo LoRa, em pedaços, até outra ponte, que o
  entrega aos telefones Bitchat perto dela. Ou chega inteiro, ou não chega: nenhum pedaço avulso vai
  ao Bitchat nem ao chat do aparelho, e quem pagou recebe a confirmação assinada pelo rádio de
  destino. Guia e roteiro de ensaio no
  [CASHU.md](https://github.com/EduChacon/Meshcore-Bitchat/blob/main/docs/bitchat/CASHU.md). No
  T-Deck Plus, os buffers da ponte ficam na PSRAM, e a RAM interna fica para o Bluetooth, o AES dos
  canais e o cartão SD.
- **Conversas privadas** (ponte `bitchat0.24`): no Bitchat, a ponte aparece na lista de pessoas como
  `LoRa bridge` e quatro caracteres. Na conversa privada com ela, basta a palavra (`bateria`,
  `quem`, `guia`, `teste`, `recado <texto>`, `sos <texto>`, `ponte`), e a resposta sai só ali.
  `@Fulano texto` manda uma mensagem direta do MeshCore ao contato Fulano, **só se ele tiver a
  estrela de favorito na tela _Contacts_** e não estiver bloqueado; a resposta aparece no chat do
  aparelho e volta ao celular em até 30 minutos, ou a qualquer hora quando começa com `@apelido`. A
  ponte lê essas mensagens. `!bridge dm off` (ou `!ponte privado off`) desliga. Com
  `!bridge tunnel on` (ou `!ponte túnel on`) nas pontes de duas casas, os celulares de uma conversam
  no privado com os da outra, de ponta a ponta, pelo canal LoRa; vem desligado, porque gasta tempo
  do canal. Detalhes no
  [guia da ponte MeshCore](https://github.com/EduChacon/Meshcore-Bitchat/blob/main/docs/bitchat/README.md).
- **Hora pelos anúncios do LoRa** (ponte `bitchat0.24`): sem telefone ou GPS com hora, a ponte acerta
  a sua pelo maior grupo de rádios MeshCore ao alcance que concordam entre si (pelo menos dois). O
  relógio do aparelho não é alterado.
- **Ensaio em aparelho:** o [roteiro](https://github.com/EduChacon/Meshcore-Bitchat/blob/main/docs/bitchat/TESTING.md)
  combinado antes da versão 1.0 vale também para o T-Deck Plus e o Cardputer ADV.

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
