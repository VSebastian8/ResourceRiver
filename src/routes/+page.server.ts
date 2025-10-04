import { mock_charts } from './mock.js';

export const actions = {
 request: async ({request, cookies}) => {
    let data = await request.formData();
    console.log(data)
 },
 provide: async ({request, cookies}) => {
    let data = await request.formData();
    console.log(data)
 }   
}