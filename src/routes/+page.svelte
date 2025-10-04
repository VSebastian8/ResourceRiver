<!-- Ok what do we need? 2 buttons: Request, Provide. These will open forms defined later (routes).
	chat pannel, each chat oon the left, opens the conversation with the first message being a map.
	Each chat has a decline/accept option -->
<!-- <p>Extra: About page, home page</p> -->
<!-- svelte-ignore a11y_click_events_have_key_events -->
<!-- svelte-ignore a11y_no_static_element_interactions -->
<script lang="ts">
	import { none, some, type Option } from 'fp-ts/lib/Option';
	import Chat, { type ChatType } from './chat.svelte';
	import { mock_charts } from './mock';
	import Provider from './provider.svelte';
	import { contains } from './provider.svelte';
	import Requester from './requester.svelte';

	let activeChat: Option<number> = $state(none);
	let chats: ChatType[] = $state(mock_charts);
	function getChat(): Option<ChatType> {
		if (activeChat._tag === 'None') {
			return none;
		} else {
			return some(chats[activeChat.value]);
		}
	}

	function pickChat(i: number) {
		activeChat = some(i);
	}
</script>

<div class="flex flex-col bg-white h-screen w-screen">
	<!-- Buttons -->
	<div class="flex items-center w-screen justify-center mt-5">
		<Provider />
		<Requester />
	</div>
	<div class="flex m-5 overflow-scroll flex-1 h-full rounded-2xl">
		<aside class=" w-1/4 text-indigo-900 p-4 bg-indigo-200 border-r-indigo-400 border-r-2">
			{#each chats as chat, i}
				<div
					onclick={() => {
						pickChat(i);
					}}
					class={'cursor-pointer  hover:bg-indigo-400 rounded-sm mb-2 p-2 ' +
						(contains(activeChat, i) ? 'bg-indigo-400 text-white' : 'bg-indigo-300')}
				>
					{chat.name}
				</div>
			{/each}
		</aside>
		<main class="flex flex-col flex-1 bg-indigo-300">
			<Chat chat={getChat()} />
		</main>
	</div>
</div>
