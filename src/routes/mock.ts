import { type ChatType } from './chat.svelte';
let mock_charts: ChatType[] = [
      { name: 'Rob', messages: [
        {msg: "Hello there Jacob!", sender: false, timestamp: new Date(1478708162000)},
        {msg: "Hi!", sender: true, timestamp: new Date(1478708162000)},
        {msg: "How've you been?", sender: true, timestamp: new Date(1478708162000)},
        {msg: "Pretty good, hbu?", sender: false, timestamp: new Date(1478708162000)},
        {msg: "Same", sender: true, timestamp: new Date(1478708162000)},
        {msg: "aight", sender: false, timestamp: new Date(1478708162000)},
        {msg: "Good talk.", sender: false, timestamp: new Date(1478708162000)},
        {msg: "See ya!", sender: false, timestamp: new Date(1478708162000)},
        {msg: "See ya!", sender: true, timestamp: new Date(1478708162000)},

      ] },
      { name: 'Bob', messages: [] },
      { name: 'Cobb', messages: [] }
  ];
export {mock_charts}