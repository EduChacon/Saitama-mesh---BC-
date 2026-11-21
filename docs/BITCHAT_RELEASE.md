# Saitama + Bitchat

Saitama (sistema para T-Deck e Cardputer ADV sobre o MeshCore) com a ponte Bitchat embutida.
**Versão experimental: compila para as duas placas e nunca foi ligada em aparelho.**

> **Cardputer ADV: não use a versão com ponte por enquanto.** Ensaiada em aparelho em 2026-11-16, a
> `saitama-cardputer-adv-bitchat` fica com cerca de 4 KB de memória livre: os ajustes travam ao abrir,
> e a ponte não consegue iniciar (o canal `bitchat` não aparece). O Cardputer não tem memória extra
> (PSRAM), e o Bluetooth ligado, que a ponte exige, já deixa o Saitama no limite. Para destravar sem
> regravar: no cartão SD, em `/ops/settings.json`, trocar `"bluetooth": true` por `"bluetooth": false`.
> Para ter a ponte no Cardputer, use o firmware MeshCore com ponte
> ([`M5Stack_Cardputer_ADV_companion_radio_ble_bitchat`](https://github.com/EduChacon/Meshcore-Bitchat/releases)).
> A versão do T-Deck Plus não é afetada.

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

Ponte MeshCore `bitchat1.2`.

- **Túnel: a pessoa do outro lado fica na lista do Bitchat.** O Bitchat tira da lista, 60 segundos
  depois, quem chega retransmitido, e não manda mensagem privada a quem não está nela. Enquanto houver
  celular perto das duas pontes, a presença vai agora a cada 50 segundos (para os dois primeiros
  celulares de cada ponte), e a conversa privada abre sem esperar minutos.
- **Custo:** cerca de 5% do tempo do canal por celular nesse ritmo (estimativa); a presença só sai
  quando sobra folga no limite de rádio da ponte.
- **Não foi ligado no T-Deck nem no Cardputer.**

## Versão anterior

Ponte MeshCore `bitchat1.1`. É a primeira versão do Saitama com ponte publicada como versão normal,
e não como pré-lançamento.

- **Túnel: a conversa abre mais depressa.** O Bitchat do iPhone desiste de abrir uma conversa
  privada em cerca de 10 segundos, e pelo túnel a abertura vai e volta pelo LoRa. Agora os pedaços
  da abertura saem assim que o rádio fica livre.
- **Contadores do túnel:** `!bridge` mostra `Tunnel: out N, in M, far phones K`.
- **Configurações pelo Bitchat:** um comando de configuração escrito no `#mesh` recebe o aviso de
  que só o dono do rádio muda isso.
- O túnel foi ensaiado pelo autor com a ponte MeshCore (Heltec V3 e T1000-E); **no T-Deck e no
  Cardputer, não foi ligado.**

## Versões anteriores

Ponte MeshCore `bitchat1.0`, a versão revisada por inteiro. **As mudanças não foram ligadas no
T-Deck nem no Cardputer;** a ponte foi ensaiada pelo autor num Heltec V3 e num T1000-E.

- **Túnel ligado de fábrica:** conversa privada entre celulares perto de pontes diferentes, pelo
  LoRa. Com ele, o apelido de quem está perto do aparelho vai pelo LoRa; `!bridge tunnel off` (ou
  `!ponte túnel off`) desliga.
- **Túnel com a ponte em reserva:** quando duas pontes se ouvem pelo Bluetooth, a reserva para o
  texto público não para mais o túnel (visto em aparelho, com a ponte MeshCore).
- **Ajuda nas duas línguas:** `!ponte ajuda` ou `!bridge help` no aparelho; `ajuda` ou `help` na
  conversa privada com a ponte, no Bitchat.
- **Hora por um rádio só,** quando a ponte não tem nenhuma.

Ponte MeshCore `bitchat0.25`: correções do primeiro ensaio em aparelho das conversas privadas.

- **Resposta abaixo da pergunta.** Na conversa privada com a ponte, cada resposta aparecia acima da
  pergunta, porque o relógio da ponte pode ficar até um segundo atrás do celular e o Bitchat ordena a
  conversa pelo horário. A resposta agora sai com horário posterior ao da pergunta.
- **Configurações só pelo dono.** `túnel on` escrito no Bitchat devolvia o estado da ponte. As
  configurações nunca mudam pelo Bitchat; a ponte agora diz isso. A mensagem cita o aplicativo
  MeshCore; no Saitama, os comandos `!bridge` são digitados no próprio aparelho, em qualquer canal.
- As demais correções da `bitchat0.25` são dos rádios nRF52 e não se aplicam ao T-Deck nem ao
  Cardputer. **Não foi ligado em aparelho.**

Ponte MeshCore `bitchat0.24`, pensada para ficar meses sem troca. **Nada do que é novo foi ligado
em aparelho;** passou nos testes em computador e compila para as duas placas.

- **Conversa privada com a ponte.** No Bitchat, a ponte aparece na lista de pessoas como
  `LoRa bridge` e quatro caracteres; abre-se com ela uma conversa privada como com qualquer pessoa.
  Ali basta a palavra (`bateria`, `quem`, `guia`, `teste`, `recado <texto>`, `sos <texto>`, ou
  `ponte` para o estado), e a resposta sai só nessa conversa. A criptografia é a mesma das conversas
  entre telefones (Noise).
- **Mensagem a um contato do LoRa.** Na conversa privada com a ponte, `@Fulano texto` vai ao contato
  Fulano do aparelho como mensagem direta do MeshCore, com o apelido de quem escreveu, **só se
  Fulano tiver a estrela de favorito na tela _Contacts_ do Saitama** (e não estiver bloqueado). A
  resposta dele aparece no chat do aparelho, como sempre, e volta à mesma conversa do Bitchat em até
  30 minutos, ou a qualquer hora quando começa com `@apelido`. Se o celular estiver longe, a resposta
  espera até 24 horas. A ponte lê essas mensagens (não é ponta a ponta). `!bridge dm off` (ou
  `!ponte privado off`) desliga.
- **Conversa privada entre celulares de casas diferentes**, de ponta a ponta, pelo LoRa: com
  `!bridge tunnel on` (ou `!ponte túnel on`) nas pontes das duas casas, cada celular vê no Bitchat
  quem está perto da outra ponte e conversa com ele no privado. As pontes só carregam os pacotes
  criptografados. Vem desligado, porque gasta tempo do canal compartilhado.
- **Hora pelos anúncios do LoRa.** Sem telefone ou GPS com hora, a ponte acerta a sua pelo maior
  grupo de rádios MeshCore ao alcance que concordam entre si (pelo menos dois). O relógio do
  aparelho não é alterado.

- **Pagamentos Cashu pelo LoRa** (ponte MeshCore `bitchat0.23`, que reúne as `bitchat0.20` a
  `0.23`): um token Cashu colado no chat público do Bitchat perto do aparelho vai pelo LoRa, em
  pedaços, até outra ponte, que o entrega aos telefones Bitchat perto dela. O token chega inteiro ou
  não chega: nenhum pedaço avulso vai ao Bitchat nem ao chat do aparelho, e quem pagou recebe no
  `#mesh` a confirmação assinada pelo rádio de destino (ou o aviso de que o token continua com ele).
  Guia e roteiro de ensaio no
  [CASHU.md](https://github.com/EduChacon/Meshcore-Bitchat/blob/main/docs/bitchat/CASHU.md).
- **Nenhum pedaço de token do LoRa chega ao Bitchat** como texto comum.
- **Bluetooth reiniciado:** se a pilha do Bluetooth recomeçar, a ponte recomeça com ela, em vez de
  ficar calada.
- **T-Deck Plus:** os buffers da ponte passam para a PSRAM; a RAM interna fica para o Bluetooth, o
  AES dos canais e o cartão SD.
- **Só compilado e testado no computador; os pagamentos não foram ensaiados em aparelho.** Ensaio no
  GitHub e compilação local das duas placas aprovados antes da publicação.

- **`!bridge position on`** (ponte MeshCore `bitchat0.13`), enviado no aparelho: o socorro pedido
  pelo Bitchat passa a levar a posição do GPS, sem ligar o compartilhamento de localização. Pensado
  para trilha. `!bridge position off` desliga; vem desligado. Ensaio no GitHub e compilação local
  das duas placas aprovados antes da publicação.
- **Correções de segurança e de privacidade** (ponte MeshCore `bitchat0.12`), a partir de uma
  revisão do código: o socorro pedido pelo Bitchat só leva a posição se o compartilhamento de
  localização estiver ligado; `!ponte radios` só responde no aparelho; o recado só é trocado por um
  telefone ligado diretamente; as respostas da ponte não vão ao cartão SD; uma identidade nova do
  aparelho renova a da ponte; a biblioteca de mapas passa a ser compilada numa versão fixa.
  Ensaio no GitHub e compilação local das duas placas aprovados antes da publicação.
- **Funções da casa** (ponte MeshCore `bitchat0.11`), por comando no aparelho ou no `#mesh` do
  Bitchat: `!bridge prefix on`/`off`, `!ponte recado <texto>`, `!ponte bateria` (com aviso de
  bateria baixa), `!ponte radios`, `!ponte sos <texto>` (com a posição do GPS, se houver) e
  `!ponte teste`. Só simuladas e compiladas; o código passou por duas revisões independentes, e
  as falhas achadas foram corrigidas antes da publicação.
- **Menu de ajustes:** linhas **Bitchat** (modo da ponte) e **Bitchat saver** (modo econômico),
  sem precisar dos comandos.
- **Histórico, segunda parte:** a ponte guarda também o que os telefones escrevem no `#mesh` perto
  do aparelho, para quem chega depois (só aparece para quem já conheceu o autor).
- Das versões anteriores: `!ponte quem` (nomes ouvidos no LoRa), histórico do texto do LoRa e
  `!ponte guia`.
