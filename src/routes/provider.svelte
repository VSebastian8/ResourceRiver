<script lang="ts" module>
	export function contains<A>(o: Option<A>, x: A) {
		if (o._tag === 'Some') {
			return o.value === x;
		} else {
			return false;
		}
	}
</script>

<script lang="ts">
	import { none, some, type Option, elem } from 'fp-ts/lib/Option';
	import { Modal, Content, Trigger } from 'sv-popup';
	let activeRes: Option<number> = $state(none);
</script>

<Modal basic>
	<Content>
		<form method="POST" action="?/provide" class="flex flex-col items-center p-5">
			<div>
				<button
					class={'btn bg-indigo-300 hover:bg-indigo-500 py-2 px-4 rounded mr-2 cursor-pointer ' +
						(contains(activeRes, 0) ? 'bg-indigo-500 text-white' : 'bg-indigo-300')}
					type="button"
					onclick={() => (activeRes = some(0))}>Vehicles</button
				>
				<button
					class={'btn bg-indigo-300 hover:bg-indigo-500 py-2 px-4 rounded mr-2 cursor-pointer ' +
						(contains(activeRes, 1) ? 'bg-indigo-500 text-white' : 'bg-indigo-300')}
					type="button"
					onclick={() => (activeRes = some(1))}>Generators</button
				>
				<button
					class={'btn bg-indigo-300 hover:bg-indigo-500 py-2 px-4 rounded mr-2 cursor-pointer ' +
						(contains(activeRes, 2) ? 'bg-indigo-500 text-white' : 'bg-indigo-300')}
					type="button"
					onclick={() => (activeRes = some(2))}>Skills</button
				>
			</div>
			<label class="mt-5">
				Quantity
				<input name="quantity" type="number" required class="rounded-sm ml-2" />
			</label>
			<button
				type="submit"
				class="btn bg-indigo-500 hover:bg-indigo-700 text-white font-bold py-2 px-4 rounded mt-5 cursor-pointer"
				>Provide</button
			>
		</form>
	</Content>
	<Trigger>
		<button
			class="btn bg-indigo-500 hover:bg-indigo-700 text-white font-bold py-2 px-4 rounded mr-2 cursor-pointer"
			>Provide</button
		>
	</Trigger>
</Modal>
