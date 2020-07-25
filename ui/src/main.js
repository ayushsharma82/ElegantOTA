import SparkMD5 from 'spark-md5';
import Vue from 'vue';
import App from './App.vue';

Vue.config.productionTip = false;
Object.defineProperty(Vue.prototype, 'SparkMD5', { value: SparkMD5 });

new Vue({
  render: (h) => h(App),
}).$mount('#app');
