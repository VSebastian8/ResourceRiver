<script lang="ts" module>
	export type MessageType = {
		msg: string;
		sender: boolean;
		timestamp: Date;
	};
	export type ChatType = {
		name: string;
		senderAcc: boolean;
		receiverAcc: boolean;
		messages: MessageType[];
	};
</script>

<script lang="ts">
	import { type Option } from 'fp-ts/lib/Option';
	import MapLibre from 'svelte-maplibre/MapLibre.svelte';
	import DefaultMarker from 'svelte-maplibre/DefaultMarker.svelte';
	let { chat }: { chat: Option<ChatType> } = $props();
</script>

{#if chat._tag == 'None'}
	<MapLibre
		style="https://basemaps.cartocdn.com/gl/positron-gl-style/style.json"
		class="relative aspect-[4/4] max-h-[30vh] sm:max-h-full"
		zoom={4.5}
		center={[30, 65]}
	>
		<DefaultMarker lngLat={[22.2687918, 60.4491839]} />
		<DefaultMarker lngLat={[25.2248233, 60.2516994]} />
	</MapLibre>
{:else}
	<div class="w-full text-indigo-900 bg-indigo-200 border-b-2 border-b-indigo-400 m-0 p-2">
		Selected chat {chat.value.name}
	</div>
	<div class="flex flex-1 flex-col overflow-scroll pl-20 pr-15">
		<!-- Message Container -->
		{#each chat.value.messages as message}
			{#if message.sender}
				<div class="flex gap-5 bg-indigo-400 w-fit p-2 rounded-b-md rounded-tl-md mt-1 self-end">
					<p class="block text-white">{message.msg}</p>
					<p class="block mt-3 text-indigo-200">
						{message.timestamp.getHours()}:{message.timestamp.getMinutes()}
					</p>
				</div>
			{:else}
				<div class="flex gap-5 bg-indigo-200 w-fit p-2 rounded-b-md rounded-tr-md mt-1">
					<p>{message.msg}</p>
					<p class="block mt-3 text-indigo-400">
						{message.timestamp.getHours()}:{message.timestamp.getMinutes()}
					</p>
				</div>
			{/if}
		{/each}
	</div>
	<div class=" rounded-4xl text-indigo-900 bg-indigo-200 border-b-indigo-400 m-5 p-5 pl-15">
		Type a message...
	</div>
{/if}
