<script lang="ts" module>
	export type MessageType = {
		msg: string;
		sender: boolean;
		timestamp: Date;
	};
	export type ChatType = {
		name: string;
		messages: MessageType[];
	};
</script>

<script lang="ts">
	import { none, some, type Option } from 'fp-ts/lib/Option';
	let { chat }: { chat: Option<ChatType> } = $props();
</script>

{#if chat._tag == 'None'}
	<h1>No chat selected</h1>
{:else}
	<div class="w-full text-indigo-900 bg-indigo-200 border-b-2 border-b-indigo-400 m-0 p-2">
		Selected chat {chat.value.name}
	</div>
	<div class="flex flex-col overflow-scroll pl-20 pr-15">
		<!-- Message Container -->
		{#each chat.value.messages as message}
			{#if message.sender}
				<div class="bg-indigo-400 w-fit p-2 rounded-b-md rounded-tl-md mt-1 self-end text-white">
					{message.msg}
				</div>
			{:else}
				<div class="bg-indigo-200 w-fit p-2 rounded-b-md rounded-tr-md mt-1">{message.msg}</div>
			{/if}
		{/each}
	</div>
{/if}
