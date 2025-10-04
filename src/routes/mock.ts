import { type ChatType } from './chat.svelte';
let mock_charts: ChatType[] = [
      { name: 'Rob', 
        senderAcc: false,
        receiverAcc: true,
        messages: [
        {msg: "Hello there Jacob!", sender: false, timestamp: new Date(1478708162000)},
        {msg: "Hi!", sender: true, timestamp: new Date(1478708172000)},
        {msg: "How've you been?", sender: true, timestamp: new Date(1478708222000)},
        {msg: "Pretty good, hbu?", sender: false, timestamp: new Date(1478708232000)},
        {msg: "Same", sender: true, timestamp: new Date(1478708252000)},
        {msg: "aight", sender: false, timestamp: new Date(1478708252000)},
        {msg: "Good talk.", sender: false, timestamp: new Date(1478708302000)},
        {msg: "See ya!", sender: false, timestamp: new Date(1478708302000)},
        {msg: "See ya!", sender: true, timestamp: new Date(1478708452000)},
      ] },
      { name: 'Bob', senderAcc: false, receiverAcc: false, messages: [] },
      { name: 'Cobb', senderAcc: true, receiverAcc: false, messages: [] }
  ];
export {mock_charts}